#include "lwImageViewer2D.h"

#include <vtkCamera.h>
#include <vtkPropPicker.h>
#include <vtkCoordinate.h>
#include <vtkTextProperty.h>
#include <vtkProperty.h>
#include "vtkImageInteractionCallback.h"

unsigned int lwImageViewer2D::id = 0;

lwImageViewer2D::lwImageViewer2D()
{
	_image = vtkSmartPointer<vtkImageData>::New();
	_resliceAxes = vtkSmartPointer<vtkMatrix4x4>::New();
	_reslice = vtkSmartPointer<vtkImageReslice>::New();
	_table = vtkSmartPointer<vtkLookupTable>::New();
	_color = vtkSmartPointer<vtkImageMapToColors>::New();
	_actor = vtkSmartPointer<vtkImageActor>::New();
	_renderer = vtkSmartPointer<vtkRenderer>::New();
	_window = vtkSmartPointer<vtkRenderWindow>::New();
	_interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	_imageStyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
	_callback = vtkSmartPointer<vtkImageInteractionCallback>::New();

	_reslice->SetInputData(_image);
	_reslice->SetOutputDimensionality(2);
	_reslice->SetResliceAxes(_resliceAxes);
	_reslice->SetInterpolationModeToLinear();

	_table->SetRange(-400, 1300);				// image intensity range
	_table->SetValueRange(0.0, 1.0);			// from black to white
	_table->SetSaturationRange(0.0, 0.0);		// no color saturation
	_table->SetRampToLinear();
	_table->Build();

	_color->SetLookupTable(_table);
	_color->SetInputConnection(_reslice->GetOutputPort());

	_actor->GetMapper()->SetInputConnection(_color->GetOutputPort());
	_renderer->AddActor(_actor);
	_window->AddRenderer(_renderer);
	_interactor->SetInteractorStyle(_imageStyle);
	_window->SetInteractor(_interactor);

	_callback->SetImageReslice(_reslice);
	_callback->SetInteractor(_interactor);
	_callback->SetRenderer(_renderer);
	_callback->SetViewer2D(this);

	_imageStyle->AddObserver(vtkCommand::MouseMoveEvent, _callback);
	_imageStyle->AddObserver(vtkCommand::LeftButtonPressEvent, _callback);
	_imageStyle->AddObserver(vtkCommand::LeftButtonReleaseEvent, _callback);
	_imageStyle->AddObserver(vtkCommand::MouseWheelForwardEvent, _callback);
	_imageStyle->AddObserver(vtkCommand::MouseWheelBackwardEvent, _callback);

	wid = id;
	id++;

	_firstRender = true;
}


lwImageViewer2D::~lwImageViewer2D()
{

}

void lwImageViewer2D::SetInputImage(vtkSmartPointer<vtkImageData> input)
{
	_image = input;
	int		extent[6];
	double	spacing[3];
	double	origin[3];

	_image->GetExtent(extent);
	_image->GetSpacing(spacing);
	_image->GetOrigin(origin);

	//_center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
	//_center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
	//_center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);
	for (size_t i = 0; i < 3; i++)
	{
		_center[i] = 0;
	}

	_reslice->SetInputData(_image);
}


void lwImageViewer2D::SetOrientation(ORIENTATION_TYPE orient)
{
	_orientation = orient;
	switch (orient)
	{
	case CORONAL:
		_resliceAxes->DeepCopy(CoronalElements);
		_resliceAxes->SetElement(0, 3, _center[0]);
		_resliceAxes->SetElement(1, 3, _center[1]);
		_resliceAxes->SetElement(2, 3, _center[2]);
		break;
	case SAGITTAL:
		_resliceAxes->DeepCopy(SagittalElements);
		_resliceAxes->SetElement(0, 3, _center[0]);
		_resliceAxes->SetElement(1, 3, _center[1]);
		_resliceAxes->SetElement(2, 3, _center[2]);
		break;
	default:
		_resliceAxes->DeepCopy(AxialElements);
		_resliceAxes->SetElement(0, 3, _center[0]);
		_resliceAxes->SetElement(1, 3, _center[1]);
		_resliceAxes->SetElement(2, 3, _center[2]);
		break;
	}
}

//#include "vtkRulerWidget.h"

#include <thread>


void lwImageViewer2D::Render()
{
	if (_firstRender)
	{
		//auto ruler = vtkSmartPointer<vtkRulerWidget>::New();
		//ruler->SetCurrentRenderer(_renderer);
		//ruler->SetInteractor(_interactor);
		//ruler->On();

		_renderer->ResetCamera();
		_renderer->GetActiveCamera()->ParallelProjectionOn();
		_renderer->GetActiveCamera()->SetParallelScale(_scale);
		_window->Render();

		if (IsMaster())
		{
			_interactor->Start();
		}

		_firstRender = false;
	}
	else
	{
		_window->Render();
	}
}

void lwImageViewer2D::SetColorWindow(int win)
{
}

void lwImageViewer2D::SetColorLevel(int level)
{
}

int lwImageViewer2D::GetColorWindow()
{
	return 0;
}

int lwImageViewer2D::GetColorLevel()
{
	return 0;
}

void lwImageViewer2D::SetWindowSize(int width, int height)
{
	_window->SetSize(width, height);
}

int * lwImageViewer2D::GetWindowSize()
{
	return nullptr;
}

void lwImageViewer2D::UpdateCursorPosition(int* pos)
{
}

void lwImageViewer2D::SetShowCursor(bool flag)
{
}

void lwImageViewer2D::SetShowFullWindow(bool flag)
{
	// 计算scale
	auto h = _window->GetSize()[1];
	auto w = _window->GetSize()[0];
	int*	extent = _image->GetExtent();
	double* spacing = _image->GetSpacing();

	auto	xd = (extent[1] - extent[0])*spacing[0];
	auto	yd = (extent[3] - extent[2])*spacing[1];
	auto	zd = (extent[5] - extent[4])*spacing[2];

	auto s0 = (double)h / w;
	auto s1 = zd / yd;
	auto s2 = zd / xd;
	auto s3 = yd / xd;

	auto scale1 = (s0 > s1 ? s0 : s1)*yd*0.5;
	auto scale2 = (s0 > s2 ? s0 : s2)*xd*0.5;
	auto scale3 = (s0 > s3 ? s0 : s3)*xd*0.5;

	switch (_orientation)
	{
	case CORONAL:
		_scale = scale2;
		break;
	case SAGITTAL:
		_scale = scale1;
		break;
	default:
		_scale = scale3;
		break;
	}
}


void lwImageViewer2D::SetShowOrientationAnnotation(bool flag)
{
	_orientation_annotation = vtkSmartPointer<vtkCornerAnnotation>::New();
	_orientation_annotation->SetMaximumFontSize(25);
	if (this->_orientation == SAGITTAL)
	{
		_orientation_annotation->SetText(7, "[S]");
		_orientation_annotation->SetText(4, "[I]");
		_orientation_annotation->SetText(5, "[P]");
		_orientation_annotation->SetText(6, "[A]");

		InitCursor(this->_orientation);
	}
	else if (this->_orientation == CORONAL)
	{
		_orientation_annotation->SetText(7, "[S]");
		_orientation_annotation->SetText(4, "[I]");
		_orientation_annotation->SetText(5, "[L]");
		_orientation_annotation->SetText(6, "[R]");
		InitCursor(this->_orientation);
	}
	else if (this->_orientation == AXIAL)
	{
		_orientation_annotation->SetText(7, "[A]");
		_orientation_annotation->SetText(4, "[P]");
		_orientation_annotation->SetText(5, "[L]");
		_orientation_annotation->SetText(6, "[R]");
		InitCursor(this->_orientation);
	}
	_orientation_annotation->GetTextProperty()->SetColor(1, 1, 1);
	_renderer->AddActor(_orientation_annotation);
	_renderer->AddActor(_horizontalline_actor);
	_renderer->AddActor(_verticalline_actor);
}


#include <Windows.h>
#include <Stringapiset.h>

std::string string_To_UTF8(const std::string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	ZeroMemory(pwBuf, nwLen * 2 + 2);
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char * pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);
	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	std::string retStr(pBuf);
	delete[]pwBuf;
	delete[]pBuf;
	pwBuf = NULL;
	pBuf = NULL;
	return retStr;
}

void lwImageViewer2D::SetDicomInfoAnnotation(vtkCornerAnnotation::TextPosition i,
	const char* info)
{
	_corner_annotation = vtkSmartPointer<vtkCornerAnnotation>::New();
	_corner_annotation->SetMaximumFontSize(20);
	_corner_annotation->GetTextProperty()->SetColor(1, 1, 1);
	_corner_annotation->GetTextProperty()->SetFontFamily(VTK_FONT_FILE);
	_corner_annotation->GetTextProperty()->SetFontFile("MSYH.TTF");
	_corner_annotation->SetText(i, string_To_UTF8(info).c_str());

	_renderer->AddActor(_corner_annotation);
}


void lwImageViewer2D::SetLeftButtonInteractionStyle(INTERACTION_TYPE & type)
{
	LeftButtonInteractionStyle = type;
}

void lwImageViewer2D::SetRightButtonInteractionStyle(INTERACTION_TYPE & type)
{
	RightButtonInteractionStyle = type;
}

void lwImageViewer2D::SetMiddleButtonInteractionStyle(INTERACTION_TYPE & type)
{
	MiddleButtonInteractionStyle = type;
}

void lwImageViewer2D::SetWheelInteractionStyle(INTERACTION_TYPE & type)
{
	WheelInteractionStyle = type;
}

#include "lwDef.h"

void lwImageViewer2D::LinkNextViewer(lwImageViewer2D* w)
{
	next = w;
}

// 同步更新位置
void lwImageViewer2D::UpdatePosition(double* pos)
{
	lwImageViewer2D* p = this;
	do
	{
		cout << "Window[" << wid << "] = " << val <<
			"		Update = [" << pos[0] << "," <<
			pos[1] << "," << pos[2] << "]" << endl;

		for (size_t i = 0; i < 3; i++)
		{
			p->_cursorPosition[i] = pos[i];
		}

		double x = 0;
		double y = 0;
		double max_x = 0;
		double max_y = 0;
		double min_x = 0;
		double min_y = 0;

		double* spacing = p->_image->GetSpacing();
		double* origin = p->_image->GetOrigin();
		double *imBounds = p->_image->GetBounds();

		// check if pos lies inside image bounds
		if (pos[0]<imBounds[0] || pos[0]>imBounds[1] ||
			pos[1]<imBounds[2] || pos[1]>imBounds[3] ||
			pos[2]<imBounds[4] || pos[2]>imBounds[5])
		{
			// we are outside image bounds
			return;
		}

		pos[0] = double(rint((pos[0] - origin[0]) / spacing[0]))*spacing[0] + origin[0];
		pos[1] = double(rint((pos[1] - origin[1]) / spacing[1]))*spacing[1] + origin[1];
		pos[2] = double(rint((pos[2] - origin[2]) / spacing[2]))*spacing[2] + origin[2];

		switch (p->_orientation)
		{
		case SAGITTAL:
			p->_reslice->SetResliceAxesOrigin(pos[0], 0, 0);
			x = (double)pos[1];
			y = (double)pos[2];
			min_x = imBounds[2];//*-1.0;
			max_x = imBounds[3];//*-1.0;
			min_y = imBounds[4];
			max_y = imBounds[5];
			break;

		case CORONAL:
			p->_reslice->SetResliceAxesOrigin(0, pos[1], 0);
			x = (double)pos[0];
			y = (double)pos[2];
			min_x = imBounds[0];//*-1.0;
			max_x = imBounds[1];//*-1.0;
			min_y = imBounds[4];
			max_y = imBounds[5];
			break;

		case AXIAL:
			p->_reslice->SetResliceAxesOrigin(0, 0, pos[2]);
			x = (double)pos[0];
			y = -(double)pos[1];
			min_x = imBounds[0];
			max_x = imBounds[1];
			min_y = -imBounds[2];
			max_y = -imBounds[3];
			break;
		}

		p->_horizontalline_source->SetPoint1(min_x, y, 0.001);
		p->_horizontalline_source->SetPoint2(max_x, y, 0.001);
		p->_verticalline_source->SetPoint1(x, min_y, 0.001);
		p->_verticalline_source->SetPoint2(x, max_y, 0.001);

		//this->_reslice->Update(); // needed to update input Extent

		p->_horizontalline_source->Modified();
		p->_verticalline_source->Modified();

		p->_interactor->Render();
		p = p->next;
	} while (p && p != this);
}


void lwImageViewer2D::SetInteractor(vtkSmartPointer<vtkRenderWindowInteractor> interactor)
{
	_interactor = interactor;
	_interactor->SetInteractorStyle(_imageStyle);
	_window->SetInteractor(_interactor);
	_callback->SetInteractor(_interactor);
}


void lwImageViewer2D::InitCursor(ORIENTATION_TYPE type)
{
	_horizontalline_actor = vtkSmartPointer<vtkActor>::New();
	_verticalline_actor = vtkSmartPointer<vtkActor>::New();
	_horizontalline_source = vtkSmartPointer<vtkLineSource>::New();
	_verticalline_source = vtkSmartPointer<vtkLineSource>::New();
	_horizontalline_mappper = vtkSmartPointer<vtkPolyDataMapper>::New();
	_verticalline_mappper = vtkSmartPointer<vtkPolyDataMapper>::New();

	double imBounds[6];
	_image->GetBounds(imBounds);
	int	dims[3];
	double	_position[3];
	double* origin = _image->GetOrigin();
	int*	extent = _image->GetExtent();
	double* spacing = _image->GetSpacing();
	_image->GetDimensions(dims);

	for (int i = 0; i < 3; i++)
	{
		_position[i] = dims[i] / 2;
		_cursorPosition[i] = _position[i] * spacing[i] + origin[i];
	}

	UpdatePosition(_cursorPosition);

	_horizontalline_mappper->SetInputConnection(_horizontalline_source->GetOutputPort());
	_horizontalline_actor->SetMapper(_horizontalline_mappper);
	_horizontalline_actor->GetProperty()->SetColor(1.0, 0.0, 0.0);

	_verticalline_mappper->SetInputConnection(_verticalline_source->GetOutputPort());
	_verticalline_actor->SetMapper(_verticalline_mappper);
	_verticalline_actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
}

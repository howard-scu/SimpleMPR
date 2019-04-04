#include "lwMPRImageViewer.h"

#include <vtkImageMapper3D.h>
#include <vtkCamera.h>
#include <vtkProperty.h>

lwMPRImageViewer::lwMPRImageViewer()
{
	image = vtkSmartPointer<vtkImageData>::New();
	reslice = vtkSmartPointer<vtkImageReslice>::New();
	resliceAxes = vtkSmartPointer<vtkMatrix4x4>::New();
	table = vtkSmartPointer<vtkLookupTable>::New();
	color = vtkSmartPointer<vtkImageMapToColors>::New();
	actor = vtkSmartPointer<vtkImageActor>::New();
	renderer = vtkSmartPointer<vtkRenderer>::New();
	window = vtkSmartPointer<vtkRenderWindow>::New();
	interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	imageStyle = vtkSmartPointer<vtkInteractorStyleImage>::New();
	callback = vtkSmartPointer<lwMPRImageInteractionCallback>::New();

	reslice->SetInputData(image);
	reslice->SetOutputDimensionality(2);
	reslice->SetResliceAxes(resliceAxes);
	reslice->SetInterpolationModeToLinear();

	table->SetRange(0, 1300);					// image intensity range
	table->SetValueRange(0.0, 1.0);				// from black to white
	table->SetSaturationRange(0.0, 0.0);		// no color saturation
	table->SetRampToLinear();
	table->Build();

	color->SetLookupTable(table);
	color->SetInputConnection(reslice->GetOutputPort());

	actor->GetMapper()->SetInputConnection(color->GetOutputPort());
	renderer->AddActor(actor);
	window->AddRenderer(renderer);
	interactor->SetInteractorStyle(imageStyle);
	window->SetInteractor(interactor);

	callback->SetRenderer(renderer);
	callback->SetViewer(this);
	imageStyle->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
	imageStyle->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback);
	imageStyle->AddObserver(vtkCommand::MouseWheelBackwardEvent, callback);
	imageStyle->AddObserver(vtkCommand::MouseWheelForwardEvent, callback);
	imageStyle->AddObserver(vtkCommand::MouseMoveEvent, callback);

	InitCursor();
}


lwMPRImageViewer::~lwMPRImageViewer()
{

}

#include <vtkImageChangeInformation.h>

void lwMPRImageViewer::SetInput(vtkSmartPointer<vtkImageData> input)
{
	vtkSmartPointer<vtkImageChangeInformation> change =
		vtkSmartPointer<vtkImageChangeInformation>::New();
	change->SetInputData(input);
	change->CenterImageOn();
	change->Update();

	image = change->GetOutput();
	reslice->SetInputData(image);
	callback->SetInput(image);
}

vtkSmartPointer<vtkImageData> lwMPRImageViewer::GetInput()
{
	return image;
}

vtkSmartPointer<vtkImageActor> lwMPRImageViewer::GetImageActor()
{
	return actor;
}

#include <vtkMetaImageWriter.h>
#include <time.h>

string getTime()
{
	struct tm t;	// tm结构指针
	time_t now;		// 声明time_t类型变量
	time(&now);     // 获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间

	char buf[255];
	sprintf_s(buf, "%02d%02d%02d.mha", t.tm_hour,
		t.tm_min,
		t.tm_sec);
	return buf;
}


void lwMPRImageViewer::Render()
{
	vtkMatrix4x4::Multiply4x4(lwMPRLogic::axis_matrix, lwMPRLogic::view_matrix, resliceAxes);
	reslice->SetResliceAxes(resliceAxes);
	reslice->Modified();
	UpdateCursor();
	//renderer->ResetCamera();

	//auto writer = vtkSmartPointer<vtkMetaImageWriter>::New();
	//writer->SetInputConnection(reslice->GetOutputPort());
	//writer->SetFileName(getTime().c_str());
	//writer->Write();
	window->Render();

	if (!render_flag)
	{
		//renderer->GetActiveCamera()->ParallelProjectionOn();
		//renderer->GetActiveCamera()->SetParallelScale(60);
		render_flag = true;
		window->Render();

		if (view_type == SAGITTAL)
			interactor->Start();
	}
}


void lwMPRImageViewer::InitCursor()
{
	_horizontalline_actor = vtkSmartPointer<vtkActor>::New();
	_verticalline_actor = vtkSmartPointer<vtkActor>::New();
	_horizontalline_source = vtkSmartPointer<vtkLineSource>::New();
	_verticalline_source = vtkSmartPointer<vtkLineSource>::New();
	_horizontalline_mappper = vtkSmartPointer<vtkPolyDataMapper>::New();
	_verticalline_mappper = vtkSmartPointer<vtkPolyDataMapper>::New();

	_horizontalline_mappper->SetInputConnection(_horizontalline_source->GetOutputPort());
	_horizontalline_actor->SetMapper(_horizontalline_mappper);
	_horizontalline_actor->GetProperty()->SetColor(1.0, 0.0, 0.0);

	_verticalline_mappper->SetInputConnection(_verticalline_source->GetOutputPort());
	_verticalline_actor->SetMapper(_verticalline_mappper);
	_verticalline_actor->GetProperty()->SetColor(1.0, 0.0, 0.0);

	renderer->AddActor(_horizontalline_actor);
	renderer->AddActor(_verticalline_actor);
}

void lwMPRImageViewer::UpdateCursor()
{
	double x = 0;
	double y = 0;
	double max_x = 0;
	double max_y = 0;
	double min_x = 0;
	double min_y = 0;

	double* spacing = image->GetSpacing();
	double* origin = image->GetOrigin();
	double* imBounds = image->GetBounds();

	switch (view_type)
	{
	case SAGITTAL:
	{
		auto pos = GetPosition();
		x = pos[1];
		y = pos[2];
		min_x = imBounds[2];
		max_x = imBounds[3];
		min_y = imBounds[4];
		max_y = imBounds[5];
		break;
	}
	case CORONAL:
	{
		auto pos = GetPosition();
		x = pos[0];
		y = pos[2];
		min_x = imBounds[0];
		max_x = imBounds[1];
		min_y = imBounds[4];
		max_y = imBounds[5];
		break;
	}
	case AXIAL:
	{
		auto pos = GetPosition();
		x = pos[0];
		y = pos[1];
		min_x = imBounds[0];
		max_x = imBounds[1];
		min_y = imBounds[2];
		max_y = imBounds[3];
		break;
	}
	}
	_horizontalline_source->SetPoint1(min_x, y, 0.001);
	_horizontalline_source->SetPoint2(max_x, y, 0.001);
	_verticalline_source->SetPoint1(x, min_y, 0.001);
	_verticalline_source->SetPoint2(x, max_y, 0.001);
	_horizontalline_source->Modified();
	_verticalline_source->Modified();
}



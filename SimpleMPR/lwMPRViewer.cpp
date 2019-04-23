#include "lwMPRViewer.h"
#include <vtkImageMapper3D.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkCommand.h>
#include <vtkImageChangeInformation.h>


lwMPRViewer::lwMPRViewer()
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
	window->SetSize(600, 400);

	reslice->SetInputData(image);
	reslice->SetOutputDimensionality(2);
	reslice->SetResliceAxes(resliceAxes);
	reslice->SetInterpolationModeToLinear();

	table->SetRange(-600, 2300);				// image intensity range
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

	callback = vtkSmartPointer<lwMPRCallback>::New();

	imageStyle->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
	imageStyle->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback);
	imageStyle->AddObserver(vtkCommand::MouseWheelBackwardEvent, callback);
	imageStyle->AddObserver(vtkCommand::MouseWheelForwardEvent, callback);
	imageStyle->AddObserver(vtkCommand::MouseMoveEvent, callback);

	InitCursor();
}


lwMPRViewer::~lwMPRViewer()
{

}


void lwMPRViewer::SetInput(vtkSmartPointer<vtkImageData> input)
{
	vtkSmartPointer<vtkImageChangeInformation> change =
		vtkSmartPointer<vtkImageChangeInformation>::New();
	change->SetInputData(input);
	change->CenterImageOn();
	change->Update();

	image = change->GetOutput();
	reslice->SetInputData(image);
	callback->SetViewer(this);
}


void lwMPRViewer::Render(double theta)
{
	reslice->SetResliceAxes(this->view_mat);
	reslice->Update();
	UpdateCursor();

	renderer->ResetCamera();
	//cout << renderer->GetActiveCamera()->GetRoll() << endl;
	
	window->Render();
	if (!render_flag)
	{
		render_flag = true;
		if (this->GetView() == SAGITTAL)
			interactor->Start();
	}
}

void lwMPRViewer::InitCursor()
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

	_vert_picker = vtkSmartPointer<vtkCellPicker>::New();
	_vert_picker->PickFromListOn();
	_vert_picker->AddPickList(_verticalline_actor);
	_vert_picker->SetTolerance(0.02);

	_hori_picker = vtkSmartPointer<vtkCellPicker>::New();
	_hori_picker->PickFromListOn();
	_hori_picker->AddPickList(_horizontalline_actor);
	_hori_picker->SetTolerance(0.02);

	callback->SetHoriPicker(_hori_picker);
	callback->SetVertPicker(_vert_picker);
	callback->SetRenderer(renderer);
}

#define PI 3.1415926

void lwMPRViewer::UpdateCursor()
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

	double min = 9999;
	double max = -9999;
	for (int i = 0; i < 6; i++)
	{
		if (min > imBounds[i]) min = imBounds[i];
		if (max < imBounds[i]) max = imBounds[i];
	}

	switch (this->GetView())
	{
	case SAGITTAL:
	{
		x = this->GetYPos();
		y = this->GetZPos();
		min_x = imBounds[2];
		max_x = imBounds[3];
		min_y = imBounds[4];
		max_y = imBounds[5];
		break;
	}
	case CORONAL:
	{
		x = this->GetXPos();
		y = this->GetZPos();
		min_x = imBounds[0];
		max_x = imBounds[1];
		min_y = imBounds[4];
		max_y = imBounds[5];
		break;
	}
	case AXIAL:
	{
		x = this->GetXPos();
		y = this->GetYPos();
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


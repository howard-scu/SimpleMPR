#include "lwMPRImageViewer.h"

#include <vtkImageMapper3D.h>
#include <vtkCamera.h>

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
	imageStyle = vtkSmartPointer<vtkInteractorStyleUser>::New();
	callback = vtkSmartPointer<lwMPRImageInteractionCallback>::New();

	reslice->SetInputData(image);
	reslice->SetOutputDimensionality(2);
	reslice->SetResliceAxes(resliceAxes);
	reslice->SetInterpolationModeToLinear();

	table->SetRange(-400, 1300);				// image intensity range
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
	interactor->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
	interactor->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback);
	interactor->AddObserver(vtkCommand::MouseWheelBackwardEvent, callback);
	interactor->AddObserver(vtkCommand::MouseWheelForwardEvent, callback);
	interactor->AddObserver(vtkCommand::MouseMoveEvent, callback);
}


lwMPRImageViewer::~lwMPRImageViewer()
{

}

void lwMPRImageViewer::SetInput(vtkSmartPointer<vtkImageData> input)
{
	image = input;
	reslice->SetInputData(input);
}

vtkSmartPointer<vtkImageData> lwMPRImageViewer::GetInput()
{
	return image;
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
	//auto writer = vtkSmartPointer<vtkMetaImageWriter>::New();
	//writer->SetInputConnection(reslice->GetOutputPort());
	//writer->SetFileName(getTime().c_str());
	//writer->Write();
	renderer->ResetCamera();
	window->Render();
	if (!render_flag && (view_type == SAGITTAL))
	{
		renderer->ResetCamera();
		//renderer->GetActiveCamera()->ParallelProjectionOn();
		//renderer->GetActiveCamera()->SetParallelScale();
		window->Render();
		render_flag = true;
		interactor->Start();
	}
}



#include "qtssddemo.h"
#include <iostream>
using namespace std;

QtSsdDemo::QtSsdDemo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	ui.threshold->setValue(400);
	ui.threshold->setMinimum(-400);
	ui.threshold->setMaximum(2000);

	connect(ui.threshold, SIGNAL(valueChanged(int)), this, SLOT(on_threshold_changed(int)));
}

QtSsdDemo::~QtSsdDemo()
{

}

void QtSsdDemo::on_threshold_changed(int)
{
	surface2->SetValue(0, ui.threshold->value());
	interactor->Render();
}


void QtSsdDemo::on_btn_clicked()
{
	reader =
		vtkSmartPointer<vtkDICOMImageReader>::New();
	reader->SetDirectoryName("E:\\CarotidAnalyze\\VirtualEndoscopy\\data\\Head");
	reader->Update();

	//surface =
	//	vtkSmartPointer<vtkMarchingCubes>::New();
	//surface->SetInputConnection(reader->GetOutputPort());
	//surface->ComputeNormalsOff();
	//surface->SetValue(0, 400);
	surface2 =
		vtkSmartPointer<vtkFlyingEdges3D>::New();
	surface2->SetInputConnection(reader->GetOutputPort());
	//surface2->ComputeNormalsOff();
	surface2->SetValue(0, 400);
	surface2->Update();

	renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->SetBackground(.1, .2, .3);

	renderWindow =
		vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);

	interactor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);

	mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(surface2->GetOutputPort());
	mapper->ScalarVisibilityOff();

	actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	renderer->AddActor(actor);

	renderWindow->Render();
	interactor->Start();
}
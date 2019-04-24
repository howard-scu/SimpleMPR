#include "qtmprdemo.h"
#define PI 3.1415926
#include <iostream>
#include <vtkImageChangeInformation.h>

using namespace std;

QtMprDemo::QtMprDemo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

}

QtMprDemo::~QtMprDemo()
{

}

#include <vtkInformation.h>

void QtMprDemo::init()
{
	// ∂¡»°
	auto reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	reader->SetDirectoryName("E:\\CarotidAnalyze\\VirtualEndoscopy\\data\\Head");
	reader->Update();

	auto change = vtkSmartPointer<vtkImageChangeInformation>::New();
	change->SetInputConnection(reader->GetOutputPort());
	change->CenterImageOn();
	change->Update();

	input = change->GetOutput();

	//reader->GetOutputInformation(0)->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
	change->GetOutput()->GetSpacing(spacing);
	change->GetOutput()->GetExtent(extent);
	change->GetOutput()->GetOrigin(origin);

	ui.x->setRange(extent[0], extent[1]);
	ui.y->setRange(extent[2], extent[3]);
	ui.z->setRange(extent[4], extent[5]);

	ui.x->setValue(extent[1] / 2);
	ui.y->setValue(extent[3] / 2);
	ui.z->setValue(extent[5] / 2);

	ui.ax->setRange(0, 36);
	ui.ay->setRange(0, 36);
	ui.az->setRange(0, 36);

	ui.x->setValue(extent[1] / 2);
	ui.y->setValue(extent[3] / 2);
	ui.z->setValue(extent[5] / 2);

	connect(ui.ax, SIGNAL(valueChanged(int)), this, SLOT(on_axpos_changed(int)));
	connect(ui.ay, SIGNAL(valueChanged(int)), this, SLOT(on_aypos_changed(int)));
	connect(ui.az, SIGNAL(valueChanged(int)), this, SLOT(on_azpos_changed(int)));
	connect(ui.x, SIGNAL(valueChanged(int)), this, SLOT(on_xpos_changed(int)));
	connect(ui.y, SIGNAL(valueChanged(int)), this, SLOT(on_ypos_changed(int)));
	connect(ui.z, SIGNAL(valueChanged(int)), this, SLOT(on_zpos_changed(int)));
	connect(ui.slice, SIGNAL(valueChanged(int)), this, SLOT(on_slice_changed(int)));

	// Set the slice orientation
	resliceAxes = vtkSmartPointer<vtkMatrix4x4>::New();
	resliceAxes->DeepCopy(axialElements);

	view = vtkSmartPointer<vtkMatrix4x4>::New();
	view->DeepCopy(axialElements);

	axis = vtkSmartPointer<vtkMatrix4x4>::New();
	axis->DeepCopy(axialElements);

	trans = vtkSmartPointer<vtkMatrix4x4>::New();
	trans->DeepCopy(axialElements);

	// Extract a slice in the desired orientation
	reslice = vtkSmartPointer<vtkImageReslice>::New();
	reslice->SetInputConnection(change->GetOutputPort());
	reslice->SetOutputDimensionality(2);
	reslice->SetResliceAxes(resliceAxes);
	reslice->SetInterpolationModeToLinear();

	// Create a greyscale lookup table
	vtkSmartPointer<vtkLookupTable> table =
		vtkSmartPointer<vtkLookupTable>::New();
	table->SetRange(-300, 700); // image intensity range
	table->SetValueRange(0.0, 1.0); // from black to white
	table->SetSaturationRange(0.0, 0.0); // no color saturation
	table->SetRampToLinear();
	table->Build();

	// Map the image through the lookup table
	vtkSmartPointer<vtkImageMapToColors> color =
		vtkSmartPointer<vtkImageMapToColors>::New();
	color->SetLookupTable(table);
	color->SetInputConnection(reslice->GetOutputPort());

	// Display the image
	vtkSmartPointer<vtkImageActor> actor =
		vtkSmartPointer<vtkImageActor>::New();
	actor->GetMapper()->SetInputConnection(color->GetOutputPort());

	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);

	window = vtkSmartPointer<vtkRenderWindow>::New();
	window->AddRenderer(renderer);

	// Set up the interaction
	vtkSmartPointer<vtkInteractorStyleImage> imageStyle =
		vtkSmartPointer<vtkInteractorStyleImage>::New();
	interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetInteractorStyle(imageStyle);
	window->SetInteractor(interactor);
	window->SetSize(600, 400);
	window->Render();

	interactor->Start();
}

void QtMprDemo::on_btnA_clicked()
{
	if (!is_init)
	{
		is_init = true;
		init();
	}
	else
	{
		axis->DeepCopy(axialElements);
		view->DeepCopy(axialElements);
		vtkMatrix4x4::Multiply4x4(axis, view, resliceAxes);
		resliceAxes->Modified();
		interactor->Render();
	}
}

void QtMprDemo::on_btnS_clicked()
{
	if (!is_init)
	{
		is_init = true;
		init();
	}
	else
	{
		axis->DeepCopy(axialElements);
		view->DeepCopy(sagittalElements);
		vtkMatrix4x4::Multiply4x4(axis, view, resliceAxes);
		resliceAxes->Modified();
		interactor->Render();
	}
}

void QtMprDemo::on_btnC_clicked()
{
	if (!is_init)
	{
		is_init = true;
		init();
	}
	else
	{
		axis->DeepCopy(axialElements);
		view->DeepCopy(coronalElements);
		vtkMatrix4x4::Multiply4x4(axis, view, resliceAxes);
		resliceAxes->Modified();
		interactor->Render();
	}
}

void QtMprDemo::on_slice_changed(int val)
{
	double point[4];
	double center[4];
	point[0] = 0.0;
	point[1] = 0.0;
	point[2] = 1.0;
	point[3] = 1.0;
	resliceAxes->MultiplyPoint(point, center);
	resliceAxes->SetElement(0, 3, center[0]);
	resliceAxes->SetElement(1, 3, center[1]);
	resliceAxes->SetElement(2, 3, center[2]);
	resliceAxes->Modified();
	interactor->Render();
}

void QtMprDemo::on_rx_btn_clicked()
{
	double t = ui.rx_val->text().toInt() / 180.0 * PI;
	double array[] = {
		1,0,0,0,
		0,cos(t),-sin(t),0,
		0,sin(t),cos(t),0,
		0,0,0,1
	};
	trans->DeepCopy(array);
	vtkMatrix4x4::Multiply4x4(axis, trans, axis);
	vtkMatrix4x4::Multiply4x4(axis, view, resliceAxes);
	resliceAxes->Modified();
	interactor->Render();
}

void QtMprDemo::on_ry_btn_clicked()
{
	double t = ui.ry_val->text().toInt() / 180.0 * PI;
	double array[] = {
		cos(t),0,sin(t),0,
		0,1,0,0,
		-sin(t),0,cos(t),0,
		0,0,0,1
	};
	trans->DeepCopy(array);
	vtkMatrix4x4::Multiply4x4(axis, trans, axis);
	vtkMatrix4x4::Multiply4x4(axis, view, resliceAxes);
	resliceAxes->Modified();
	interactor->Render();
}

void QtMprDemo::on_rz_btn_clicked()
{
	double t = ui.rz_val->text().toInt() / 180.0 * PI;
	double array[] = {
		cos(t),-sin(t),0,0,
		sin(t),cos(t),0,0,
		0,0,1,0,
		0,0,0,1
	};
	trans->DeepCopy(array);
	vtkMatrix4x4::Multiply4x4(axis, trans, axis);
	vtkMatrix4x4::Multiply4x4(axis, view, resliceAxes);
	resliceAxes->Modified();
	interactor->Render();
}

void QtMprDemo::on_xpos_changed(int val)
{
	auto current = origin[0] + spacing[0] * val;

	resliceAxes->SetElement(0, 3, current);
	resliceAxes->Modified();
	interactor->Render();
}

void QtMprDemo::on_ypos_changed(int val)
{
	auto current = origin[1] + spacing[1] * val;

	resliceAxes->SetElement(1, 3, current);
	resliceAxes->Modified();
	interactor->Render();
}

void QtMprDemo::on_zpos_changed(int val)
{
	auto current = origin[2] + spacing[2] * val;

	resliceAxes->SetElement(2, 3, current);
	resliceAxes->Modified();
	interactor->Render();
}

void QtMprDemo::on_axpos_changed(int val)
{
	a = PI / 18 * val;
	cout << "Alpha = " << a << endl;

	double array[] =
	{
	cos(b)*cos(g), -cos(a)*sin(g) + sin(a)*sin(b)*cos(g), sin(a)*sin(g) + cos(a)*sin(b)*cos(g), 0,
		cos(b)*sin(g), cos(a)*cos(g) + sin(a)*sin(b)*sin(g), -sin(a)*cos(g) + cos(a)*sin(b)*sin(g), 0,
		-sin(b), sin(a)*cos(b), cos(a)*cos(b), 0,
		0, 0, 0, 1
	};

	axis->DeepCopy(array);
	vtkMatrix4x4::Multiply4x4(axis, view, resliceAxes);
	resliceAxes->Modified();
	interactor->Render();
}

void QtMprDemo::on_aypos_changed(int val)
{
	b = PI / 18 * val;
	cout << "Beta  = " << b << endl;

	double array[] =
	{
		cos(b)*cos(g), -cos(a)*sin(g) + sin(a)*sin(b)*cos(g), sin(a)*sin(g) + cos(a)*sin(b)*cos(g), 0,
		cos(b)*sin(g), cos(a)*cos(g) + sin(a)*sin(b)*sin(g), -sin(a)*cos(g) + cos(a)*sin(b)*sin(g), 0,
		-sin(b), sin(a)*cos(b), cos(a)*cos(b), 0,
		0, 0, 0, 1
	};
	axis->DeepCopy(array);
	vtkMatrix4x4::Multiply4x4(axis, view, resliceAxes);
	resliceAxes->Modified();
	interactor->Render();
}

void QtMprDemo::on_azpos_changed(int val)
{
	g = PI / 18 * val;
	cout << "Gamma  = " << g << endl;
	double array[] =
	{
		cos(b)*cos(g), -cos(a)*sin(g) + sin(a)*sin(b)*cos(g), sin(a)*sin(g) + cos(a)*sin(b)*cos(g), 0,
		cos(b)*sin(g), cos(a)*cos(g) + sin(a)*sin(b)*sin(g), -sin(a)*cos(g) + cos(a)*sin(b)*sin(g), 0,
		-sin(b), sin(a)*cos(b), cos(a)*cos(b), 0,
		0, 0, 0, 1
	};
	axis->DeepCopy(array);
	vtkMatrix4x4::Multiply4x4(axis, view, resliceAxes);
	resliceAxes->Modified();
	interactor->Render();
}
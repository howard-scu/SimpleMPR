#include "qtmipdemo.h"

QtMipDemo::QtMipDemo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	reader = vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName("c:\\1.mha");
	reader->Update();

	renderer = vtkSmartPointer<vtkRenderer>::New();
	
	window = vtkSmartPointer<vtkRenderWindow>::New();
	window->AddRenderer(renderer);

	interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(window);
	//interactor->SetDesiredUpdateRate(frameRate / (1 + clip));
	
	mapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
	mapper->SetInputConnection(reader->GetOutputPort());

	property = vtkSmartPointer<vtkVolumeProperty>::New();
	//property->SetIndependentComponents(independentComponents);
	property->SetColor(color);
	property->SetScalarOpacity(opacity);
	property->SetInterpolationTypeToLinear();

	volume = vtkSmartPointer<vtkVolume>::New();
	volume->SetProperty(property);
	volume->SetMapper(mapper);

	color = vtkSmartPointer<vtkColorTransferFunction>::New();
	opacity = vtkSmartPointer<vtkPiecewiseFunction>::New();

	ui.window->setValue(1000);
	ui.window->setMinimum(0);
	ui.window->setMaximum(1500);

	ui.level->setValue(600);
	ui.level->setMinimum(0);
	ui.level->setMaximum(1000);

	connect(ui.window, SIGNAL(valueChanged(int)), this, SLOT(on_window_changed(int)));
	connect(ui.level, SIGNAL(valueChanged(int)), this, SLOT(on_level_changed(int)));

	color->AddRGBSegment(0.0, 1.0, 1.0, 1.0, 255.0, 1.0, 1.0, 1.0);
	opacity->AddSegment(ui.level->value() - 0.5 * ui.window->value(), 0.0, 
		ui.level->value() + 0.5 * ui.window->value(), 1.0);
	mapper->SetBlendModeToMaximumIntensity();

}

QtMipDemo::~QtMipDemo()
{

}

void QtMipDemo::on_window_changed( int val)
{
	cout << ui.window->value() << endl;
	//opacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	opacity->AddSegment(ui.level->value() - 0.5 * ui.window->value(), 0.0,
		ui.level->value() + 0.5 * ui.window->value(), 1.0);
	property->SetScalarOpacity(opacity);
	volume->Update();
	interactor->Render();
}


void QtMipDemo::on_level_changed(int val)
{
	cout << ui.level->value() << endl;
	//opacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	opacity->AddSegment(ui.level->value() - 0.5 * ui.window->value(), 0.0,
		ui.level->value() + 0.5 * ui.window->value(), 1.0);
	property->SetScalarOpacity(opacity);
	volume->Update();
	interactor->Render();
}

void QtMipDemo::on_btn_clicked()
{
	window->SetSize(600, 600);
	window->Render();
	renderer->AddVolume(volume);
	renderer->ResetCamera();
	window->Render();
	interactor->Start();
}
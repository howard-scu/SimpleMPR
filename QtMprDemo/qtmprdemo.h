#ifndef QTMPRDEMO_H
#define QTMPRDEMO_H

#include <QtWidgets/QMainWindow>
#include "ui_qtmprdemo.h"
#include "vtkSmartPointer.h"
#include "vtkImageReader2.h"
#include "vtkMatrix4x4.h"
#include "vtkImageReslice.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
#include "vtkImageActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"
#include "vtkCommand.h"
#include "vtkImageData.h"
#include "vtkImageMapper3D.h"
#include "vtkStreamingDemandDrivenPipeline.h"
#include "vtkInformation.h"
#include <vtkMetaImageReader.h>
#include <vtkDICOMImageReader.h>

class QtMprDemo : public QMainWindow
{
	Q_OBJECT

public:
	QtMprDemo(QWidget *parent = 0);
	~QtMprDemo();

public slots:
	void on_btnA_clicked();
	void on_btnS_clicked();
	void on_btnC_clicked();

	void on_xpos_changed(int);
	void on_ypos_changed(int);
	void on_zpos_changed(int);
	
	void on_axpos_changed(int);
	void on_aypos_changed(int);
	void on_azpos_changed(int);
	void on_slice_changed(int);

private:
	double	spacing[3];
	double	origin[3];
	int		extent[6];
	
	Ui::QtMprDemoClass ui;
	vtkSmartPointer<vtkImageData>		input;
	vtkSmartPointer<vtkMatrix4x4>		resliceAxes;
	vtkSmartPointer<vtkImageReslice>	reslice;
	vtkSmartPointer<vtkRenderer>		renderer;
	vtkSmartPointer<vtkRenderWindow>	window;
	vtkSmartPointer<vtkRenderWindowInteractor>	interactor;

	void init();
	bool is_init{ false };
	const double axialElements[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };

	const double coronalElements[16] = {
		1, 0, 0, 0,
		0, 0, 1, 0,
		0,-1, 0, 0,
		0, 0, 0, 1 };

	const double sagittalElements[16] = {
		0, 0,1, 0,
		-1, 0, 0, 0,
		0,-1, 0, 0,
		0, 0, 0, 1 };

	double a{ 0 };
	double b{ 0 };
	double g{ 0 };
};

#endif // QTMPRDEMO_H

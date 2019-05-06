#ifndef QTMIPDEMO_H
#define QTMIPDEMO_H

#include <QtWidgets/QMainWindow>
#include "ui_qtmipdemo.h"
#include "vtkCamera.h"
#include "vtkCommand.h"
#include "vtkColorTransferFunction.h"
#include "vtkImageData.h"
#include "vtkImageResample.h"
#include "vtkPiecewiseFunction.h"
#include "vtkProperty.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkVolume.h"
#include "vtkVolumeProperty.h"
#include <vtkMetaImageReader.h>
#include <vtkSmartPointer.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include "vtkSmartVolumeMapper.h"


class QtMipDemo : public QMainWindow
{
	Q_OBJECT

public:
	QtMipDemo(QWidget *parent = 0);
	~QtMipDemo();

public slots:
	void on_btn_clicked();
	void on_window_changed(int);
	void on_level_changed(int);

private:
	Ui::QtMipDemoClass ui;
	vtkSmartPointer<vtkMetaImageReader>				reader;
	vtkSmartPointer<vtkColorTransferFunction>		color;
	vtkSmartPointer<vtkPiecewiseFunction>			opacity;
	vtkSmartPointer<vtkRenderer>					renderer;
	vtkSmartPointer<vtkRenderWindow>				window;
	vtkSmartPointer<vtkRenderWindowInteractor>		interactor;
	vtkSmartPointer<vtkSmartVolumeMapper>			mapper;
	vtkSmartPointer<vtkVolumeProperty>				property;
	vtkSmartPointer<vtkVolume>						volume;
};

#endif // QTMIPDEMO_H

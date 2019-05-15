#ifndef QTSSDDEMO_H
#define QTSSDDEMO_H

#include <QtWidgets/QMainWindow>
#include "ui_qtssddemo.h"
#include <vtkSmartPointer.h>
#include <vtkMarchingCubes.h>
#include <vtkVoxelModeller.h>
#include <vtkSphereSource.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkFlyingEdges3D.h>


class QtSsdDemo : public QMainWindow
{
	Q_OBJECT

public:
	QtSsdDemo(QWidget *parent = 0);
	~QtSsdDemo();

public slots:
	void on_btn_clicked();
	void on_threshold_changed(int);

private:
	Ui::QtSsdDemoClass ui;
	vtkSmartPointer<vtkDICOMImageReader> reader;
	vtkSmartPointer<vtkMarchingCubes> surface;
	vtkSmartPointer<vtkFlyingEdges3D> surface2;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkRenderWindow> renderWindow;
	vtkSmartPointer<vtkRenderWindowInteractor> interactor;
	vtkSmartPointer<vtkPolyDataMapper> mapper;
	vtkSmartPointer<vtkActor> actor;
	
};

#endif // QTSSDDEMO_H

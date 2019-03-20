#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingVolumeOpenGL);
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType)

// _CRT_SECURE_NO_WARNINGS

//-------------------------------------------------------------------
// lwImageViewer2D ≤‚ ‘
//-------------------------------------------------------------------
#include "lwImageViewer2D.h"
#include "lwImageReader.h"
#include "itkImageToVTKImageFilter.h"

#include <iostream>
#include <vtkMetaImageReader.h>

using namespace std;

void main()
{
	lwImageReader reader;
	reader.SetDirectory(".\\TOF3D1");
	reader.Update();

	typedef itk::ImageToVTKImageFilter<lwImageReader::ImageType>       ConnectorType;
	ConnectorType::Pointer connector = ConnectorType::New();
	connector->SetInput(reader.GetImage());
	connector->Update();

	std::string info1 = reader._patient_id + "\n" +
		reader._patient_name + "/" + reader._patient_sex + "/" + reader._patient_age + "\n" +
		reader._patient_body_examined;

	std::string info2 = reader._institution + "\n" +
		reader._manufacture + "\n" +
		reader._modality + "\n" +
		reader._station;

	std::string info3 = reader._study_id + "\n" +
		/*reader._study_date + "/" + reader._study_time + "\n" +*/
		reader._study_desc + "\n" +
		reader._scanning_sequence + "\n" +
		reader._sequence_name/* + "\n"*/
		/*+ reader._protocol_name*/;

	std::string info4 = std::string("Window : ") + reader._window + "\n" +
		std::string("Level : ") + reader._level;

	lwImageViewer2D viewer1, viewer2, viewer3;
	viewer1.SetInputImage(connector->GetOutput());
	viewer1.SetOrientation(ORIENTATION_TYPE::CORONAL);
	viewer1.SetWindowSize(600, 400);
	viewer1.SetShowFullWindow(true);
	viewer1.SetShowOrientationAnnotation(true);
	viewer1.SetDicomInfoAnnotation(vtkCornerAnnotation::UpperLeft, info1.c_str());
	viewer1.SetDicomInfoAnnotation(vtkCornerAnnotation::UpperRight, info2.c_str());
	viewer1.SetDicomInfoAnnotation(vtkCornerAnnotation::LowerLeft, info3.c_str());
	viewer1.SetDicomInfoAnnotation(vtkCornerAnnotation::LowerRight, info4.c_str());

	viewer2.SetInputImage(connector->GetOutput());
	viewer2.SetOrientation(ORIENTATION_TYPE::SAGITTAL);
	viewer2.SetWindowSize(600, 400);
	viewer2.SetShowFullWindow(true);
	viewer2.SetShowOrientationAnnotation(true);
	viewer2.SetDicomInfoAnnotation(vtkCornerAnnotation::UpperLeft, info1.c_str());
	viewer2.SetDicomInfoAnnotation(vtkCornerAnnotation::UpperRight, info2.c_str());
	viewer2.SetDicomInfoAnnotation(vtkCornerAnnotation::LowerLeft, info3.c_str());
	viewer2.SetDicomInfoAnnotation(vtkCornerAnnotation::LowerRight, info4.c_str());

	viewer3.SetInputImage(connector->GetOutput());
	viewer3.SetOrientation(ORIENTATION_TYPE::AXIAL);
	viewer3.SetWindowSize(600, 400);
	viewer3.SetShowFullWindow(true);
	viewer3.SetShowOrientationAnnotation(true);
	viewer3.SetDicomInfoAnnotation(vtkCornerAnnotation::UpperLeft, info1.c_str());
	viewer3.SetDicomInfoAnnotation(vtkCornerAnnotation::UpperRight, info2.c_str());
	viewer3.SetDicomInfoAnnotation(vtkCornerAnnotation::LowerLeft, info3.c_str());
	viewer3.SetDicomInfoAnnotation(vtkCornerAnnotation::LowerRight, info4.c_str());

	viewer1.LinkNextViewer(&viewer2);
	viewer2.LinkNextViewer(&viewer3);
	viewer3.LinkNextViewer(&viewer1);

	viewer1.Render();
	viewer2.Render();
	viewer3.Render();
}
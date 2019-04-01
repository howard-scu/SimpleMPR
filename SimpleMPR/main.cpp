#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingVolumeOpenGL);
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType)

#include "lwMPRImageViewer.h"

//void main()
//{
//	lwMPRImageViewer viewer;
//}


//
//// _CRT_SECURE_NO_WARNINGS
//
////-------------------------------------------------------------------
//// lwImageViewer2D ≤‚ ‘
////-------------------------------------------------------------------
//#include "lwImageViewer2D.h"
//#include "lwImageReader.h"
//#include "itkImageToVTKImageFilter.h"
//
//#include <iostream>
//#include <vtkMetaImageReader.h>
//
//using namespace std;
//
//void maddin()
//{
//	lwImageReader reader;
//	reader.SetDirectory(".\\TOF3D1");
//	reader.Update();
//
//	typedef itk::ImageToVTKImageFilter<lwImageReader::ImageType>       ConnectorType;
//	ConnectorType::Pointer connector = ConnectorType::New();
//	connector->SetInput(reader.GetImage());
//	connector->Update();
//
//	std::string info1 = reader._patient_id + "\n" +
//		reader._patient_name + "/" + reader._patient_sex + "/" + reader._patient_age + "\n" +
//		reader._patient_body_examined;
//
//	std::string info2 = reader._institution + "\n" +
//		reader._manufacture + "\n" +
//		reader._modality + "\n" +
//		reader._station;
//
//	std::string info3 = reader._study_id + "\n" +
//		/*reader._study_date + "/" + reader._study_time + "\n" +*/
//		reader._study_desc + "\n" +
//		reader._scanning_sequence + "\n" +
//		reader._sequence_name/* + "\n"*/
//		/*+ reader._protocol_name*/;
//
//	std::string info4 = std::string("Window : ") + reader._window + "\n" +
//		std::string("Level : ") + reader._level;
//
//	lwImageViewer2D viewer1, viewer2, viewer3;
//	//viewer1.SetInputImage(connector->GetOutput());
//	//viewer1.SetOrientation(ORIENTATION_TYPE::CORONAL);
//	//viewer1.SetWindowSize(600, 400);
//	//viewer1.SetShowFullWindow(true);
//	//viewer1.SetShowOrientationAnnotation(true);
//	//viewer1.SetDicomInfoAnnotation(vtkCornerAnnotation::UpperLeft, info1.c_str());
//	//viewer1.SetDicomInfoAnnotation(vtkCornerAnnotation::UpperRight, info2.c_str());
//	//viewer1.SetDicomInfoAnnotation(vtkCornerAnnotation::LowerLeft, info3.c_str());
//	//viewer1.SetDicomInfoAnnotation(vtkCornerAnnotation::LowerRight, info4.c_str());
//
//	//viewer2.SetInputImage(connector->GetOutput());
//	//viewer2.SetOrientation(ORIENTATION_TYPE::SAGITTAL);
//	//viewer2.SetWindowSize(600, 400);
//	//viewer2.SetShowFullWindow(true);
//	//viewer2.SetShowOrientationAnnotation(true);
//	//viewer2.SetDicomInfoAnnotation(vtkCornerAnnotation::UpperLeft, info1.c_str());
//	//viewer2.SetDicomInfoAnnotation(vtkCornerAnnotation::UpperRight, info2.c_str());
//	//viewer2.SetDicomInfoAnnotation(vtkCornerAnnotation::LowerLeft, info3.c_str());
//	//viewer2.SetDicomInfoAnnotation(vtkCornerAnnotation::LowerRight, info4.c_str());
//
//	viewer3.SetInputImage(connector->GetOutput());
//	viewer3.SetOrientation(ORIENTATION_TYPE::AXIAL);
//	viewer3.SetWindowSize(600, 400);
//	viewer3.SetShowFullWindow(true);
//	viewer3.SetShowOrientationAnnotation(true);
//	viewer3.SetDicomInfoAnnotation(vtkCornerAnnotation::UpperLeft, info1.c_str());
//	viewer3.SetDicomInfoAnnotation(vtkCornerAnnotation::UpperRight, info2.c_str());
//	viewer3.SetDicomInfoAnnotation(vtkCornerAnnotation::LowerLeft, info3.c_str());
//	viewer3.SetDicomInfoAnnotation(vtkCornerAnnotation::LowerRight, info4.c_str());
//
//	//viewer1.LinkNextViewer(&viewer2);
//	//viewer2.LinkNextViewer(&viewer3);
//	viewer3.LinkNextViewer(&viewer1);
//
//	//viewer1.Render();
//	//viewer2.Render();
//	viewer3.Render();
//}
//
////vtkSmartPointer<vtkMatrix4x4>
////makeTransform(vtkSmartPointer<vtkMatrix4x4> matrix, double angle)
////{
////	matrix->GetElement(0, 0);
////}
//
//#include <vtkMetaImageReader.h>
//#include "vtkSmartPointer.h"
//#include "vtkImageReader2.h"
//#include "vtkMatrix4x4.h"
//#include "vtkImageReslice.h"
//#include "vtkLookupTable.h"
//#include "vtkImageMapToColors.h"
//#include "vtkImageActor.h"
//#include "vtkRenderer.h"
//#include "vtkRenderWindow.h"
//#include "vtkRenderWindowInteractor.h"
//#include "vtkInteractorStyleImage.h"
//#include "vtkCommand.h"
//#include "vtkImageData.h"
//#include "vtkImageMapper3D.h"
//#include "vtkStreamingDemandDrivenPipeline.h"
//#include "vtkInformation.h"
//
//// The mouse motion callback, to turn "Slicing" on and off
//class vtkImageInteractionCallback2 : public vtkCommand
//{
//public:
//
//	static vtkImageInteractionCallback2 *New() {
//		return new vtkImageInteractionCallback2;
//	};
//
//	vtkImageInteractionCallback2() {
//		this->Slicing = 0;
//		this->ImageReslice = nullptr;
//		this->Interactor = nullptr;
//	};
//
//	void SetImageReslice(vtkImageReslice *reslice) {
//		this->ImageReslice = reslice;
//	};
//
//	vtkImageReslice *GetImageReslice() {
//		return this->ImageReslice;
//	};
//
//	void SetInteractor(vtkRenderWindowInteractor *interactor) {
//		this->Interactor = interactor;
//	};
//
//	vtkRenderWindowInteractor *GetInteractor() {
//		return this->Interactor;
//	};
//
//	void Execute(vtkObject *, unsigned long event, void *) override
//	{
//		vtkRenderWindowInteractor *interactor = this->GetInteractor();
//
//		int lastPos[2];
//		interactor->GetLastEventPosition(lastPos);
//		int currPos[2];
//		interactor->GetEventPosition(currPos);
//
//		if (event == vtkCommand::LeftButtonPressEvent)
//		{
//			this->Slicing = 1;
//		}
//		else if (event == vtkCommand::LeftButtonReleaseEvent)
//		{
//			this->Slicing = 0;
//		}
//		else if (event == vtkCommand::MouseMoveEvent)
//		{
//			if (this->Slicing)
//			{
//				vtkImageReslice *reslice = this->ImageReslice;
//
//				// Increment slice position by deltaY of mouse
//				int deltaY = lastPos[1] - currPos[1];
//
//				reslice->Update();
//				double sliceSpacing = reslice->GetOutput()->GetSpacing()[2];
//				vtkMatrix4x4 *matrix = reslice->GetResliceAxes();
//				// move the center point that we are slicing through
//				double point[4];
//				double center[4];
//				point[0] = 0.0;
//				point[1] = 0.0;
//				point[2] = sliceSpacing * deltaY;
//				point[3] = 1.0;
//				matrix->MultiplyPoint(point, center);
//				for (size_t i = 0; i < 3; i++)
//				{
//					cout << center[i] << ",";
//				}
//				cout << endl;
//
//				matrix->SetElement(0, 3, center[0]);
//				matrix->SetElement(1, 3, center[1]);
//				matrix->SetElement(2, 3, center[2]);
//				interactor->Render();
//			}
//			else
//			{
//				vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(
//					interactor->GetInteractorStyle());
//				if (style)
//				{
//					style->OnMouseMove();
//				}
//			}
//		}
//	};
//
//private:
//
//	// Actions (slicing only, for now)
//	int Slicing;
//
//	// Pointer to vtkImageReslice
//	vtkImageReslice *ImageReslice;
//
//	// Pointer to the interactor
//	vtkRenderWindowInteractor *Interactor;
//};
//
//// The program entry point
//int maiasdfasdfn(int argc, char *argv[])
//{
//	vtkSmartPointer<vtkMetaImageReader> reader = vtkSmartPointer<vtkMetaImageReader>::New();
//	reader->SetFileName("c:\\0.mha");
//	reader->Update();
//
//	// Calculate the center of the volume
//	reader->Update();
//	int extent[6];
//	double spacing[3];
//	double origin[3];
//
//	reader->GetOutputInformation(0)->Get(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent);
//	reader->GetOutput()->GetSpacing(spacing);
//	reader->GetOutput()->GetOrigin(origin);
//
//	double center[3] = {0,0,0};
//	center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
//	center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
//	center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);
//
//	// Matrices for axial, coronal, sagittal, oblique view orientations
//	static double axialElements[16] = {
//			 1, 0, 0, 0,
//			 0, 1, 0, 0,
//			 0, 0, 1, 0,
//			 0, 0, 0, 1 };
//
//	// Set the slice orientation
//	vtkSmartPointer<vtkMatrix4x4> resliceAxes =
//		vtkSmartPointer<vtkMatrix4x4>::New();
//	resliceAxes->DeepCopy(axialElements);
//	// Set the point through which to slice
//	resliceAxes->SetElement(0, 3, center[0]);
//	resliceAxes->SetElement(1, 3, center[1]);
//	resliceAxes->SetElement(2, 3, center[2]);
//
//	// Extract a slice in the desired orientation
//	vtkSmartPointer<vtkImageReslice> reslice =
//		vtkSmartPointer<vtkImageReslice>::New();
//	reslice->SetInputConnection(reader->GetOutputPort());
//	reslice->SetOutputDimensionality(2);
//	reslice->SetResliceAxes(resliceAxes);
//	reslice->SetInterpolationModeToLinear();
//
//	// Create a greyscale lookup table
//	vtkSmartPointer<vtkLookupTable> table =
//		vtkSmartPointer<vtkLookupTable>::New();
//	table->SetRange(0, 2000); // image intensity range
//	table->SetValueRange(0.0, 1.0); // from black to white
//	table->SetSaturationRange(0.0, 0.0); // no color saturation
//	table->SetRampToLinear();
//	table->Build();
//
//	// Map the image through the lookup table
//	vtkSmartPointer<vtkImageMapToColors> color =
//		vtkSmartPointer<vtkImageMapToColors>::New();
//	color->SetLookupTable(table);
//	color->SetInputConnection(reslice->GetOutputPort());
//
//	// Display the image
//	vtkSmartPointer<vtkImageActor> actor =
//		vtkSmartPointer<vtkImageActor>::New();
//	actor->GetMapper()->SetInputConnection(color->GetOutputPort());
//
//	vtkSmartPointer<vtkRenderer> renderer =
//		vtkSmartPointer<vtkRenderer>::New();
//	renderer->AddActor(actor);
//
//	vtkSmartPointer<vtkRenderWindow> window =
//		vtkSmartPointer<vtkRenderWindow>::New();
//	window->AddRenderer(renderer);
//
//	// Set up the interaction
//	vtkSmartPointer<vtkInteractorStyleImage> imageStyle =
//		vtkSmartPointer<vtkInteractorStyleImage>::New();
//	vtkSmartPointer<vtkRenderWindowInteractor> interactor =
//		vtkSmartPointer<vtkRenderWindowInteractor>::New();
//	interactor->SetInteractorStyle(imageStyle);
//	window->SetInteractor(interactor);
//	window->Render();
//
//	vtkSmartPointer<vtkImageInteractionCallback2> callback =
//		vtkSmartPointer<vtkImageInteractionCallback2>::New();
//	callback->SetImageReslice(reslice);
//	callback->SetInteractor(interactor);
//
//	imageStyle->AddObserver(vtkCommand::MouseMoveEvent, callback);
//	imageStyle->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
//	imageStyle->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback);
//
//	// Start interaction
//	// The Start() method doesn't return until the window is closed by the user
//	interactor->Start();
//
//	return EXIT_SUCCESS;
//}

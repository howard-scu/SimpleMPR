#ifndef vtkImageInteractionCallback_h
#define vtkImageInteractionCallback_h

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
#include "vtkPropPicker.h"
#include <vtkRenderer.h>
#include "lwImageViewer2D.h"

class vtkImageInteractionCallback : public vtkCommand
{
public:

	static vtkImageInteractionCallback *New()
	{
		return new vtkImageInteractionCallback;
	};

	vtkImageInteractionCallback()
	{
		this->Slicing = 0;
		this->ImageReslice = nullptr;
		this->Interactor = nullptr;
		this->Renderer = nullptr;
		prop_picker_ = vtkSmartPointer<vtkPropPicker>::New();
	};

	void SetImageReslice(vtkImageReslice *reslice)
	{
		this->ImageReslice = reslice;
	};

	void SetViewer2D(lwImageViewer2D *viewer)
	{
		this->Viewer = viewer;
	};

	vtkImageReslice *GetImageReslice()
	{
		return this->ImageReslice;
	};

	void SetRenderer(vtkRenderer* renderer)
	{
		Renderer = renderer;
	}


	void SetInteractor(vtkRenderWindowInteractor *interactor)
	{
		this->Interactor = interactor;
	};

	vtkRenderWindowInteractor *GetInteractor()
	{
		return this->Interactor;
	};

	void Execute(vtkObject *, unsigned long event, void *) override
	{
		vtkRenderWindowInteractor *interactor = this->GetInteractor();

		int lastPos[2];
		interactor->GetLastEventPosition(lastPos);
		int currPos[2];
		interactor->GetEventPosition(currPos);

		if (event == vtkCommand::LeftButtonPressEvent)
		{
			this->Slicing = 1;
		}
		else if (event == vtkCommand::LeftButtonReleaseEvent)
		{
			this->Slicing = 0;
		}
		else if (event == vtkCommand::MouseMoveEvent)
		{
			if (this->Slicing)
			{
				UpdatePostion();
			}
			else
			{
				vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(
					interactor->GetInteractorStyle());
				if (style)
				{
					style->OnMouseMove();
				}
			}
		}
		else if (event == vtkCommand::MouseWheelForwardEvent)
		{
			UpdateSlice(interactor, 1);
		}
		else if (event == vtkCommand::MouseWheelBackwardEvent)
		{
			UpdateSlice(interactor, -1);
		}
	};

private:

	// Actions (slicing only, for now)
	int Slicing;

	// Pointer to vtkImageReslice
	vtkImageReslice *ImageReslice;
	vtkRenderer* Renderer;
	// Pointer to the interactor
	vtkRenderWindowInteractor *Interactor;
	vtkSmartPointer<vtkPropPicker> prop_picker_;
	lwImageViewer2D *Viewer;

	void UpdateSlice(vtkRenderWindowInteractor *interactor, int delta)
	{
		vtkImageReslice *reslice = this->ImageReslice;

		double sliceSpacing = reslice->GetOutput()->GetSpacing()[2];
		vtkMatrix4x4 *matrix = reslice->GetResliceAxes();
		// move the center point that we are slicing through
		double point[4];
		double center[4];
		point[0] = 0.0;
		point[1] = 0.0;
		point[2] = sliceSpacing * delta;
		point[3] = 1.0;
		matrix->MultiplyPoint(point, center);
		matrix->SetElement(0, 3, center[0]);
		matrix->SetElement(1, 3, center[1]);
		matrix->SetElement(2, 3, center[2]);

		cout << "center = " << center[0] << ","
			<< center[1] << ","
			<< center[2] << endl;

		double  pts[3];
		double* current_pts = Viewer->GetPosition();
		for (size_t i = 0; i < 3; i++)
		{
			pts[i] = current_pts[i];
		}
		switch (Viewer->GetOrientation())
		{
		case SAGITTAL://1,2
			pts[0] = center[0];
			break;
		case CORONAL://0,2
			pts[1] = center[1];
			break;
		case AXIAL://0,1
			pts[2] = center[2];
			break;
		}
		reslice->Update();
		Viewer->UpdatePosition(pts);
		interactor->Render();
	}

	void UpdatePostion()
	{
		vtkRenderWindowInteractor *interactor = this->GetInteractor();

		double  wpts[2];
		prop_picker_->Pick(interactor->GetEventPosition()[0],
			interactor->GetEventPosition()[1],
			0.0, Renderer);
		prop_picker_->GetPickPosition(wpts);

		double  pts[3];
		double* current_pts;
		switch (Viewer->GetOrientation())
		{
		case SAGITTAL://1,2
			pts[1] = wpts[0];
			pts[2] = wpts[1];
			current_pts = Viewer->GetPosition();
			pts[0] = current_pts[0];
			break;
		case CORONAL://0,2
			pts[0] = wpts[0];
			pts[2] = wpts[1];
			current_pts = Viewer->GetPosition();
			pts[1] = current_pts[1];
			break;
		case AXIAL://0,1
			pts[0] = wpts[0];
			pts[1] = -wpts[1];
			current_pts = Viewer->GetPosition();
			pts[2] = current_pts[2];
			break;
		}
		Viewer->UpdatePosition(pts);
		interactor->Render();
	}
};
#endif // !vtkImageInteractionCallback_h

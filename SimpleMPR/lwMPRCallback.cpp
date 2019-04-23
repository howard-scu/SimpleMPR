#include "lwMPRCallback.h"
#include "lwMPRViewer.h"
#define PI 3.14159265

vtkStandardNewMacro(lwMPRCallback);

lwMPRCallback::lwMPRCallback()
{
	point_picker = vtkSmartPointer<vtkPropPicker>::New();
}


lwMPRCallback::~lwMPRCallback()
{
}



void lwMPRCallback::Execute(vtkObject * caller, unsigned long eventId, void * callData)
{
	vtkInteractorStyleImage *style = static_cast<vtkInteractorStyleImage*>(caller);
	auto iren = style->GetInteractor();
	double pt[3];
	switch (eventId)
	{
	case vtkCommand::LeftButtonPressEvent:
		lp = true;
		hflag = _hori_picker->Pick(iren->GetEventPosition()[0], iren->GetEventPosition()[1],
			0.0, renderer);
		vflag = _vert_picker->Pick(iren->GetEventPosition()[0], iren->GetEventPosition()[1],
			0.0, renderer);

		// Ðý×ª
		viewer->UpdateTheta(PI/2);
		break;
	case vtkCommand::LeftButtonReleaseEvent:
		lp = false;
		hflag = 0;
		vflag = 0;
		break;
	case vtkCommand::MouseMoveEvent:
	{
		if (lp && hflag && vflag)
		{
			point_picker->Pick(iren->GetEventPosition()[0],
				iren->GetEventPosition()[1],
				0.0, renderer);
			point_picker->GetPickPosition(pt);
			viewer->UpdatePosition(pt[0], pt[1]);
		}
		break;
	}

	case vtkCommand::MouseWheelBackwardEvent:
	{
		double slice = viewer->GetNSlice();
		switch (viewer->GetView())
		{
		case lwMPRLogic::AXIAL:
			slice -= spacing[2];
			break;
		case lwMPRLogic::CORONAL:
			slice -= spacing[1];
			break;
		case lwMPRLogic::SAGITTAL:
			slice -= spacing[0];
			break;
		}
		viewer->UpdateSlice(slice);
		break;
	}
	case vtkCommand::MouseWheelForwardEvent:
	{
		double slice = viewer->GetNSlice();
		switch (viewer->GetView())
		{
		case lwMPRLogic::AXIAL:
			slice += spacing[2];
			break;
		case lwMPRLogic::CORONAL:
			slice += spacing[1];
			break;
		case lwMPRLogic::SAGITTAL:
			slice += spacing[0];
			break;
		}
		viewer->UpdateSlice(slice);
		break;
	}
	default:
		break;
	}
}

void lwMPRCallback::SetViewer(lwMPRViewer * mv)
{
	viewer = mv;
	viewer->GetInput()->GetSpacing(spacing);
}


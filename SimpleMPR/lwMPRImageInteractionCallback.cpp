#include "lwMPRImageInteractionCallback.h"
#include "lwMPRImageViewer.h"


vtkStandardNewMacro(lwMPRImageInteractionCallback);

lwMPRImageInteractionCallback::lwMPRImageInteractionCallback()
{
	picker = vtkSmartPointer<vtkPropPicker>::New();
}


lwMPRImageInteractionCallback::~lwMPRImageInteractionCallback()
{
}

void lwMPRImageInteractionCallback::Execute(
	vtkObject * caller, unsigned long eventId, void * callData)
{
	vtkRenderWindowInteractor *iren = static_cast<vtkRenderWindowInteractor*>(caller);
	switch (eventId)
	{
	case vtkCommand::LeftButtonPressEvent:
	{
		lp = true;
		break;
	}
	case vtkCommand::LeftButtonReleaseEvent:
	{
		//lp = false;
		double  wpts[3];
		picker->Pick(iren->GetEventPosition()[0],
			iren->GetEventPosition()[1],
			0.0, renderer);
		picker->GetPickPosition(wpts);
		auto center = viewer->GetCenter();
		switch (viewer->GetView())
		{
		case lwMPRLogic::AXIAL:
			center[0] = wpts[0];
			center[1] = wpts[1];
			break;
		case lwMPRLogic::CORONAL:
			center[0] = wpts[0];
			center[2] = wpts[1];
			break;
		case lwMPRLogic::SAGITTAL:
			center[1] = wpts[0];
			center[2] = wpts[1];
			break;
		default:
			break;
		}
		viewer->UpdateCenter(center);
		break;
	}
	case vtkCommand::MouseMoveEvent:
	{
		//if (lp)
		//{
		//	double  wpts[3];
		//	picker->Pick(iren->GetEventPosition()[0],
		//		iren->GetEventPosition()[1],
		//		0.0, renderer);
		//	picker->GetPickPosition(wpts);
		//	auto center = viewer->GetCenter();
		//	switch (viewer->GetView())
		//	{
		//	case lwMPRLogic::AXIAL:
		//		center[0] = wpts[0];
		//		center[1] = wpts[1];
		//		break;
		//	case lwMPRLogic::CORONAL:
		//		center[0] = wpts[0];
		//		center[2] = wpts[1];
		//		break;
		//	case lwMPRLogic::SAGITTAL:
		//		center[1] = wpts[0];
		//		center[2] = wpts[1];
		//		break;
		//	default:
		//		break;
		//	}
		//	viewer->UpdateCenter(center);
		//}
		break;
	}
	case vtkCommand::MouseWheelBackwardEvent:
	{
		auto center = viewer->GetCenter();
		switch (viewer->GetView())
		{
		case lwMPRLogic::AXIAL:
			center[2] -= spacing[2];
			break;
		case lwMPRLogic::CORONAL:
			center[1] -= spacing[1];
			break;
		case lwMPRLogic::SAGITTAL:
			center[0] -= spacing[0];
			break;
		default:
			break;
		}
		viewer->UpdateCenter(center);
		break;
	}
	case vtkCommand::MouseWheelForwardEvent:
	{
		auto center = viewer->GetCenter();
		switch (viewer->GetView())
		{
		case lwMPRLogic::AXIAL:
			center[2] += spacing[2];
			break;
		case lwMPRLogic::CORONAL:
			center[1] += spacing[1];
			break;
		case lwMPRLogic::SAGITTAL:
			center[0] += spacing[0];
			break;
		default:
			break;
		}
		viewer->UpdateCenter(center);
		break;
	}
	default:
		break;
	}
}

void lwMPRImageInteractionCallback::SetRenderer(vtkSmartPointer<vtkRenderer> ren)
{
	renderer = ren;
}


void lwMPRImageInteractionCallback::SetViewer(lwMPRImageViewer* view)
{
	viewer = view;
	view->GetInput()->GetSpacing(spacing);
}

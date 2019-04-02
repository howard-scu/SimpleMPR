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
	vtkInteractorStyleImage *style = static_cast<vtkInteractorStyleImage*>(caller);
	auto iren = style->GetInteractor();
	switch (eventId)
	{
	case vtkCommand::LeftButtonPressEvent:
	{
		lp = true;
		break;
	}
	case vtkCommand::LeftButtonReleaseEvent:
	{
		lp = false;
		break;
	}
	case vtkCommand::MouseMoveEvent:
	{
		if (lp)
		{
			double  wpts[3];
			picker->Pick(iren->GetEventPosition()[0],
				iren->GetEventPosition()[1],
				0.0, renderer);
			picker->GetPickPosition(wpts);
			auto pos = viewer->GetCenter();

			switch (viewer->GetView())
			{
			case lwMPRLogic::AXIAL:
				pos[0] += (wpts[0] - center[0]);
				pos[1] += (wpts[1] - center[1]);
				break;
			case lwMPRLogic::CORONAL:
				pos[0] += (wpts[0] - center[0]);
				pos[2] += (wpts[1] - center[1]);
				break;
			case lwMPRLogic::SAGITTAL:
				pos[1] += (wpts[0] - center[0]);
				pos[2] += (wpts[1] - center[1]);
				break;
			default:
				break;
			}
			viewer->UpdateCenter(pos);
		}
		break;
	}
	case vtkCommand::MouseWheelBackwardEvent:
	{
		auto pos = viewer->GetCenter();
		switch (viewer->GetView())
		{
		case lwMPRLogic::AXIAL:
			pos[2] -= spacing[2];
			break;
		case lwMPRLogic::CORONAL:
			pos[1] -= spacing[1];
			break;
		case lwMPRLogic::SAGITTAL:
			pos[0] -= spacing[0];
			break;
		default:
			break;
		}
		viewer->UpdateCenter(pos);
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

	view->GetInput()->GetExtent(extent);
	view->GetInput()->GetSpacing(spacing);
	view->GetInput()->GetOrigin(origin);

	center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
	center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
	center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);
}

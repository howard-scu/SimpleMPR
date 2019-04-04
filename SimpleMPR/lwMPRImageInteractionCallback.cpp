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
			auto pos = viewer->GetPosition();
			switch (viewer->GetView())
			{
			case lwMPRLogic::AXIAL:
				pos[0] = wpts[0];
				pos[1] = wpts[1];
				break;
			case lwMPRLogic::CORONAL:
				pos[0] = wpts[0];
				pos[2] = wpts[1];
				break;
			case lwMPRLogic::SAGITTAL:
				pos[1] = wpts[0];
				pos[2] = wpts[1];
				break;
			}
			viewer->OnPositionChanged(pos);
		}
		break;
	}
	case vtkCommand::MouseWheelBackwardEvent:
	{
		auto pos = viewer->GetPosition();
		switch (viewer->GetView())
		{
		case lwMPRLogic::AXIAL:
			pos[2] -= image->GetSpacing()[2];
			break;
		case lwMPRLogic::CORONAL:
			pos[1] -= image->GetSpacing()[1];
			break;
		case lwMPRLogic::SAGITTAL:
			pos[0] -= image->GetSpacing()[0];
			break;
		}
		viewer->OnPositionChanged(pos);
		break;
	}
	case vtkCommand::MouseWheelForwardEvent:
	{
		auto pos = viewer->GetPosition();
		switch (viewer->GetView())
		{
		case lwMPRLogic::AXIAL:
			pos[2] += image->GetSpacing()[2];
			break;
		case lwMPRLogic::CORONAL:
			pos[1] += image->GetSpacing()[1];
			break;
		case lwMPRLogic::SAGITTAL:
			pos[0] += image->GetSpacing()[0];
			break;
		}
		viewer->OnPositionChanged(pos);
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
}

void lwMPRImageInteractionCallback::SetInput(vtkSmartPointer<vtkImageData> input)
{
	image = input;
}
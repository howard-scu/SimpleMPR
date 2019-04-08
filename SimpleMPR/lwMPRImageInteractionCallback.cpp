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


vector<double> lwMPRImageInteractionCallback::MousePick(vtkRenderWindowInteractor * iren)
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
	return pos;
}


vector<double> compute_v(vector<double> v1, vector<double> v2)
{
	vector<double> result({ 0,0,0 });
	double ss = 0.0;
	for (size_t i = 0; i < 3; i++)
	{
		result[i] = v1[i] - v2[i];
		ss += result[i] * result[i];
	}
	ss = sqrt(ss);
	for (size_t i = 0; i < 3; i++)
		result[i] /= ss;
	return result;
}

vector<double> cross(vector<double> v1, vector<double> v2)
{
	vector<double> result;
	result.push_back(v1[1] * v2[2] - v1[2] * v2[1]);
	result.push_back(v1[2] * v2[0] - v1[0] * v2[2]);
	result.push_back(v1[0] * v2[1] - v1[1] * v2[0]);
	double ss = 0.0;
	for (size_t i = 0; i < 3; i++)
	{
		ss += result[i] * result[i];
	}
	ss = sqrt(ss);
	for (size_t i = 0; i < 3; i++)
		result[i] /= ss;
	return result;
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
		hflag = _horizontalline_picker->Pick(iren->GetEventPosition()[0], iren->GetEventPosition()[1],
			0.0, renderer);
		vflag = _verticalline_picker->Pick(iren->GetEventPosition()[0], iren->GetEventPosition()[1],
			0.0, renderer);
		break;
	}
	case vtkCommand::LeftButtonReleaseEvent:
	{
		lp = false;
		hflag = 0;
		vflag = 0;
		break;
	}
	case vtkCommand::MouseMoveEvent:
	{
		if (lp && hflag && vflag)
		{
			auto pos = MousePick(iren);
			viewer->OnPositionChanged(pos);
		}
		else if (lp && hflag)
		{
			auto pos1 = viewer->GetPosition();
			auto pos2 = MousePick(iren);
			vector<double> v1 = compute_v(pos2, pos1);
			vector<double> v2 = cross(v1, viewer->GetZAxis());

			switch (viewer->GetView())
			{
			case lwMPRLogic::AXIAL:
				viewer->UpdateXAxis(v1);
				viewer->UpdateYAxis(v2);
				break;
			case lwMPRLogic::CORONAL:
				viewer->UpdateXAxis(v1);
				viewer->UpdateZAxis(v2);
				break;
			case lwMPRLogic::SAGITTAL:
				viewer->UpdateYAxis(v1);
				viewer->UpdateZAxis(v2);
				break;
			}
		}
		else if (lp&& vflag)
		{
			auto pos1 = viewer->GetPosition();
			auto pos2 = MousePick(iren);
			vector<double> v1 = compute_v(pos2, pos1);
			vector<double> v2 = cross(v1, viewer->GetZAxis());
			switch (viewer->GetView())
			{
			case lwMPRLogic::AXIAL:
				viewer->UpdateYAxis(v1);
				viewer->UpdateXAxis(v2);
				break;
			case lwMPRLogic::CORONAL:
				viewer->UpdateZAxis(v1);
				viewer->UpdateXAxis(v2);
				break;
			case lwMPRLogic::SAGITTAL:
				viewer->UpdateZAxis(v1);
				viewer->UpdateYAxis(v2);
				break;
			}
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

void lwMPRImageInteractionCallback::SetHoriPicker(vtkSmartPointer<vtkCellPicker> picker)
{
	_horizontalline_picker = picker;
}

void lwMPRImageInteractionCallback::SetVertPicker(vtkSmartPointer<vtkCellPicker> picker)
{
	_verticalline_picker = picker;
}

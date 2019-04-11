#include "lwMPRLogic.h"



lwMPRLogic::lwMPRLogic()
{
	view_matrix = vtkSmartPointer<vtkMatrix4x4>::New();
	axis_matrix = vtkSmartPointer<vtkMatrix4x4>::New();
	view_matrix->DeepCopy(AXIAL_VIEW);
	axis_matrix->DeepCopy(AXIAL_VIEW);
	next_viewer = nullptr;
}


lwMPRLogic::~lwMPRLogic()
{
}

void lwMPRLogic::SetView(MPR_TYPE type)
{
	view_type = type;
	switch (type)
	{
	case AXIAL:
		view_matrix->DeepCopy(AXIAL_VIEW);
		break;
	case CORONAL:
		view_matrix->DeepCopy(CORONAL_VIEW);
		break;
	case SAGITTAL:
		view_matrix->DeepCopy(SAGITTAL_VIEW);
		break;
	default:
		view_matrix->DeepCopy(AXIAL_VIEW);
		break;
	}
}

lwMPRLogic::MPR_TYPE lwMPRLogic::GetView()
{
	return view_type;
}

void lwMPRLogic::SyncView(lwMPRLogic* viewer)
{
	next_viewer = viewer;
}

void lwMPRLogic::OnAxisChanged(vtkSmartPointer<vtkMatrix4x4> matrix)
{
	auto ptr = this;
	do
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				ptr->axis_matrix->SetElement(i, j, matrix->GetElement(i, j));
			}
		}
		ptr->Render();
		ptr = ptr->next_viewer;
	} while (ptr&&ptr != this);
}

vector<double> lwMPRLogic::GetPosition()
{
	return position;
}

void lwMPRLogic::OnPositionChanged(vector<double>& vec)
{
	auto ptr = this;
	do
	{
		switch (ptr->view_type)
		{
		case AXIAL:
			ptr->axis_matrix->SetElement(2, 3, vec[2]);
			break;
		case CORONAL:
			ptr->axis_matrix->SetElement(1, 3, vec[1]);
			break;
		case SAGITTAL:
			ptr->axis_matrix->SetElement(0, 3, vec[0]);
			break;
		}
		for (int i = 0; i < 3; i++)
		{
			ptr->position[i] = vec[i];
		}
		ptr->Render();
		ptr = ptr->next_viewer;
	} while (ptr&&ptr != this);
}



//vector<double> lwMPRLogic::GetPosition()
//{
//	return position;
//}
//
////void lwMPRLogic::UpdatePosition(vector<double>& vec)
////{
////	position = vec;
////}
//
//void lwMPRLogic::OnPositionChanged(vector<double>& vec)
//{
//	auto ptr = this;
//	do
//	{
//		switch (ptr->view_type)
//		{
//		case AXIAL:
//			ptr->axis_matrix->SetElement(2, 3, vec[2]);
//			ptr->position[0] = vec[0];
//			ptr->position[1] = vec[1];
//			ptr->position[2] = vec[2];
//			break;
//		case CORONAL:
//			ptr->axis_matrix->SetElement(2, 3, vec[1]);
//			ptr->position[0] = vec[0];
//			ptr->position[1] = vec[2];
//			ptr->position[2] = vec[1];
//			break;
//		case SAGITTAL:
//			ptr->axis_matrix->SetElement(2, 3, vec[0]);
//			ptr->position[0] = vec[1];
//			ptr->position[1] = vec[2];
//			ptr->position[2] = vec[0];
//			break;
//		}
//
//		ptr->Render();
//		ptr = ptr->next_viewer;
//	} while (ptr&&ptr != this);
//}

//void lwMPRLogic::UpdateZSlice(vector<double>& vec)
//{
//	auto ptr = this;
//	do
//	{
//		if (ptr->view_type == this->view_type)
//			ptr->OnZSliceChanged(vec);
//		else
//			ptr->OnXYPosChanged(vec);
//		ptr->Render();
//		ptr = ptr->next_viewer;
//	} while (ptr&&ptr != this);
//}
//
//void lwMPRLogic::UpdateXYPos(vector<double>& vec)
//{
//	auto ptr = this;
//	do
//	{
//		if (ptr->view_type == this->view_type)
//			ptr->OnXYPosChanged(vec);
//		else
//			ptr->OnZSliceChanged(vec);
//		ptr->Render();
//		ptr = ptr->next_viewer;
//	} while (ptr&&ptr != this);
//}
//
//void lwMPRLogic::OnZSliceChanged(vector<double>& pos)
//{
//	switch (view_type)
//	{
//	case AXIAL:
//		axis_matrix->SetElement(2, 3, pos[2]);
//		break;
//	case CORONAL:
//		axis_matrix->SetElement(2, 3, pos[1]);
//		break;
//	case SAGITTAL:
//		axis_matrix->SetElement(2, 3, pos[0]);
//		break;
//	}
//}
//
//void lwMPRLogic::OnXYPosChanged(vector<double>& pos)
//{
//	switch (view_type)
//	{
//	case AXIAL:
//		x_pos = pos[0];
//		y_pos = pos[1];
//		break;
//	case CORONAL:
//		x_pos = pos[0];
//		y_pos = pos[2];
//		break;
//	case SAGITTAL:
//		x_pos = pos[1];
//		y_pos = pos[2];
//		break;
//	}
//}

//vector<double> lwMPRLogic::GetCenter()
//{
//	switch (view_type)
//	{
//	case AXIAL:
//		return vector<double>{x_pos, y_pos, axis_matrix->GetElement(2, 3)};
//	case CORONAL:
//		return vector<double>{x_pos, axis_matrix->GetElement(2, 3), y_pos};
//	case SAGITTAL:
//		return vector<double>{axis_matrix->GetElement(2, 3), x_pos, y_pos};
//	}
//	return vector<double>{0,0,0};
//}

void lwMPRLogic::UpdateXAxis(vector<double>& vec)
{
	for (int i = 0; i < 3; i++)
	{
		axis_matrix->SetElement(i, 0, vec[i]);
	}
	OnAxisChanged(axis_matrix);
}

void lwMPRLogic::UpdateYAxis(vector<double>& vec)
{
	for (int i = 0; i < 3; i++)
	{
		axis_matrix->SetElement(i, 1, vec[i]);
	}
	OnAxisChanged(axis_matrix);
}

void lwMPRLogic::UpdateZAxis(vector<double>& vec)
{
	for (int i = 0; i < 3; i++)
	{
		axis_matrix->SetElement(i, 2, vec[i]);
	}
	OnAxisChanged(axis_matrix);
}

vector<double> lwMPRLogic::GetXAxis()
{
	vector<double> vec;
	for (int i = 0; i < 3; i++)
	{
		vec.push_back(axis_matrix->GetElement(i, 0));
	}
	return vec;
}

vector<double> lwMPRLogic::GetYAxis()
{
	vector<double> vec;
	for (int i = 0; i < 3; i++)
	{
		vec.push_back(axis_matrix->GetElement(i, 1));
	}
	return vec;
}

vector<double> lwMPRLogic::GetZAxis()
{
	vector<double> vec;
	for (int i = 0; i < 3; i++)
	{
		vec.push_back(axis_matrix->GetElement(i, 2));
	}
	return vec;
}


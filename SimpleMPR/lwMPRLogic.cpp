#include "lwMPRLogic.h"



lwMPRLogic::lwMPRLogic()
{
	view_matrix = vtkSmartPointer<vtkMatrix4x4>::New();
	axis_matrix = vtkSmartPointer<vtkMatrix4x4>::New();
	trans_matrix = vtkSmartPointer<vtkMatrix4x4>::New();
	view_matrix->DeepCopy(AXIAL_VIEW);
	axis_matrix->DeepCopy(AXIAL_VIEW);
	next_viewer = nullptr;
}


lwMPRLogic::~lwMPRLogic()
{
}

void lwMPRLogic::SetView(MPR_TYPE type)
{
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

void lwMPRLogic::SyncView(lwMPRLogic* viewer)
{
	next_viewer = viewer;
}

void lwMPRLogic::OnAxisMatrixChanged(vtkSmartPointer<vtkMatrix4x4> matrix)
{
	auto p = this;
	do
	{
		p->axis_matrix->DeepCopy(matrix);
		p = p->next_viewer;
	} while (p&&p != this);
}

void lwMPRLogic::UpdateXAxis(vector<double>& vec)
{
	for (int i = 0; i < 3; i++)
	{
		axis_matrix->SetElement(i, 0, vec[i]);
	}
	OnAxisMatrixChanged(axis_matrix);
}

void lwMPRLogic::UpdateYAxis(vector<double>& vec)
{
	for (int i = 0; i < 3; i++)
	{
		axis_matrix->SetElement(i, 1, vec[i]);
	}
	OnAxisMatrixChanged(axis_matrix);
}

void lwMPRLogic::UpdateZAxis(vector<double>& vec)
{
	for (int i = 0; i < 3; i++)
	{
		axis_matrix->SetElement(i, 2, vec[i]);
	}
	OnAxisMatrixChanged(axis_matrix);
}

void lwMPRLogic::UpdateCenter(vector<double>& vec)
{
	for (int i = 0; i < 3; i++)
	{
		axis_matrix->SetElement(i, 3, vec[i]);
	}
	OnAxisMatrixChanged(axis_matrix);
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

vector<double> lwMPRLogic::GetCenter()
{
	vector<double> vec;
	for (int i = 0; i < 3; i++)
	{
		vec.push_back(axis_matrix->GetElement(i, 3));
	}
	return vec;
}

void lwMPRLogic::Render()
{
	vtkMatrix4x4::Multiply4x4(axis_matrix, view_matrix, trans_matrix);
}

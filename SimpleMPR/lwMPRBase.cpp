#include "lwMPRBase.h"



lwMPRBase::lwMPRBase()
{
	Init();
}


lwMPRBase::~lwMPRBase()
{
}

void lwMPRBase::SetView(MPR_TYPE type)
{
	view = type;
	switch (type)
	{
	case lwMPRBase::AXIAL:
		view_mat->DeepCopy(AXIAL_VIEW);
		break;
	case lwMPRBase::CORONAL:
		view_mat->DeepCopy(CORONAL_VIEW);
		break;
	case lwMPRBase::SAGITTAL:
		view_mat->DeepCopy(SAGITTAL_VIEW);
		break;
	}
}

lwMPRBase::MPR_TYPE
lwMPRBase::GetView()
{
	return view;
}

vtkSmartPointer<vtkMatrix4x4> lwMPRBase::GetTransfromMatrix()
{
	rotation_x_mat->Modified();
	rotation_y_mat->Modified();
	rotation_z_mat->Modified();
	view_mat->Modified();
	auto trans1 = vtkSmartPointer<vtkMatrix4x4>::New();
	auto trans2 = vtkSmartPointer<vtkMatrix4x4>::New();
	auto trans3 = vtkSmartPointer<vtkMatrix4x4>::New();
	vtkMatrix4x4::Multiply4x4(rotation_z_mat, rotation_y_mat, trans1);
	vtkMatrix4x4::Multiply4x4(rotation_x_mat, view_mat, trans2);
	vtkMatrix4x4::Multiply4x4(trans1, trans2, trans3);
	return trans3;
}

void lwMPRBase::Init()
{
	rotation_x_mat = vtkSmartPointer<vtkMatrix4x4>::New();
	rotation_y_mat = vtkSmartPointer<vtkMatrix4x4>::New();
	rotation_z_mat = vtkSmartPointer<vtkMatrix4x4>::New();
	view_mat = vtkSmartPointer<vtkMatrix4x4>::New();

	rotation_x_mat->Identity();
	rotation_y_mat->Identity();
	rotation_z_mat->Identity();
	view_mat->Identity();
}


void lwMPRBase::SetAlpha(double a)
{
	alpha = a;
	rotation_x_mat->SetElement(1, 1, cos(alpha));
	rotation_x_mat->SetElement(2, 1, sin(alpha));
	rotation_x_mat->SetElement(1, 2, -sin(alpha));
	rotation_x_mat->SetElement(2, 2, cos(alpha));
	rotation_x_mat->Modified();
}

void lwMPRBase::SetBeta(double b)
{
	beta = b;
	rotation_y_mat->SetElement(0, 0, cos(beta));
	rotation_y_mat->SetElement(2, 0, -sin(beta));
	rotation_y_mat->SetElement(0, 2, sin(beta));
	rotation_y_mat->SetElement(2, 2, cos(beta));
	rotation_y_mat->Modified();
}

void lwMPRBase::SetGamma(double g)
{
	gamma = g;
	rotation_z_mat->SetElement(0, 0, cos(gamma));
	rotation_z_mat->SetElement(1, 0, sin(gamma));
	rotation_z_mat->SetElement(0, 1, -sin(gamma));
	rotation_z_mat->SetElement(1, 1, cos(gamma));
	rotation_z_mat->Modified();
}
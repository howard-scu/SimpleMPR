#include "lwMPRBase.h"



lwMPRBase::lwMPRBase()
{
	Init();
}


lwMPRBase::~lwMPRBase()
{
}

void lwMPRBase::Init()
{
	view_mat = vtkSmartPointer<vtkMatrix4x4>::New();
	view_mat->Identity();
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

void lwMPRBase::SetAlpha(double a)
{
	switch (view)
	{
	case lwMPRBase::AXIAL:
		alpha = a;
		break;
	case lwMPRBase::CORONAL:
		alpha = a;
		break;
	case lwMPRBase::SAGITTAL:
		alpha = a;
		break;
	}

	auto rotation_x_mat = vtkSmartPointer<vtkMatrix4x4>::New();
	rotation_x_mat->Identity();

	rotation_x_mat->SetElement(1, 1, cos(alpha));
	rotation_x_mat->SetElement(2, 1, sin(alpha));
	rotation_x_mat->SetElement(1, 2, -sin(alpha));
	rotation_x_mat->SetElement(2, 2, cos(alpha));
	rotation_x_mat->Modified();

	vtkMatrix4x4::Multiply4x4(rotation_x_mat, view_mat, view_mat);
	view_mat->Modified();
}

void lwMPRBase::SetBeta(double b)
{
	switch (view)
	{
	case lwMPRBase::AXIAL:
		beta = b;
		break;
	case lwMPRBase::CORONAL:
		beta = b;
		break;
	case lwMPRBase::SAGITTAL:
		beta = -b;
		break;
	}

	auto rotation_y_mat = vtkSmartPointer<vtkMatrix4x4>::New();
	rotation_y_mat->Identity();

	rotation_y_mat->SetElement(0, 0, cos(beta));
	rotation_y_mat->SetElement(2, 0, -sin(beta));
	rotation_y_mat->SetElement(0, 2, sin(beta));
	rotation_y_mat->SetElement(2, 2, cos(beta));
	rotation_y_mat->Modified();

	vtkMatrix4x4::Multiply4x4(rotation_y_mat, view_mat, view_mat);
	view_mat->Modified();
}

void lwMPRBase::SetGamma(double g)
{
	switch (view)
	{
	case lwMPRBase::AXIAL:
		gamma = g;
		break;
	case lwMPRBase::CORONAL:
		gamma = -g;
		break;
	case lwMPRBase::SAGITTAL:
		gamma = -g;
		break;
	}
	auto rotation_z_mat = vtkSmartPointer<vtkMatrix4x4>::New();
	rotation_z_mat->Identity();

	rotation_z_mat->SetElement(0, 0, cos(gamma));
	rotation_z_mat->SetElement(1, 0, sin(gamma));
	rotation_z_mat->SetElement(0, 1, -sin(gamma));
	rotation_z_mat->SetElement(1, 1, cos(gamma));
	rotation_z_mat->Modified();

	vtkMatrix4x4::Multiply4x4(rotation_z_mat, view_mat, view_mat);
	view_mat->Modified();
}


void lwMPRBase::SetXPos(double mx)
{
	xpos = mx;
	if (this->GetView() == SAGITTAL)
		view_mat->SetElement(0, 3, mx);
}

void lwMPRBase::SetYPos(double my)
{
	ypos = my;
	if (this->GetView() == CORONAL)
		view_mat->SetElement(1, 3, my);
}

void lwMPRBase::SetZPos(double mz)
{
	zpos = mz;
	if (this->GetView() == AXIAL)
		view_mat->SetElement(2, 3, mz);
}
#include "lwMPRBase.h"



lwMPRBase::lwMPRBase()
{
	axis = vtkSmartPointer<vtkMatrix4x4>::New();
}


lwMPRBase::~lwMPRBase()
{
}

void lwMPRBase::SetView(MPR_TYPE type)
{
	view = type;
	switch (view)
	{
	case lwMPRBase::AXIAL:
		axis->DeepCopy(AXIAL_VIEW);
		hv = vector<double>{ 1,0,0 };
		vv = vector<double>{ 0,1,0 };
		break;
	case lwMPRBase::CORONAL:
		axis->DeepCopy(CORONAL_VIEW);
		hv = vector<double>{ 1,0,0 };
		vv = vector<double>{ 0,0,1 };
		break;
	case lwMPRBase::SAGITTAL:
		axis->DeepCopy(SAGITTAL_VIEW);
		hv = vector<double>{ 0,1,0 };
		vv = vector<double>{ 0,0,1 };
		break;
	}
}

lwMPRBase::MPR_TYPE
lwMPRBase::GetView()
{
	return view;
}

vector<double> lwMPRBase::GetXAxis()
{
	vector<double> result(3, 0.0);
	for (int i = 0; i < 3; i++)
	{
		switch (view)
		{
		case lwMPRBase::AXIAL:
			result[i] = axis->GetElement(i, 0);
			break;
		case lwMPRBase::CORONAL:
			result[i] = axis->GetElement(i, 0);
			break;
		case lwMPRBase::SAGITTAL:
			result[i] = axis->GetElement(i, 2);
			break;
		}
	}
	return result;
}

vector<double> lwMPRBase::GetYAxis()
{
	vector<double> result(3, 0.0);
	for (int i = 0; i < 3; i++)
	{
		switch (view)
		{
		case lwMPRBase::AXIAL:
			result[i] = axis->GetElement(i, 1);
			break;
		case lwMPRBase::CORONAL:
			result[i] = axis->GetElement(i, 2);
			break;
		case lwMPRBase::SAGITTAL:
			result[i] = axis->GetElement(i, 0);
			break;
		}
	}
	return result;
}

vector<double> lwMPRBase::GetZAxis()
{
	vector<double> result(3, 0.0);
	for (int i = 0; i < 3; i++)
	{
		switch (view)
		{
		case lwMPRBase::AXIAL:
			result[i] = axis->GetElement(i, 2);
			break;
		case lwMPRBase::CORONAL:
			result[i] = axis->GetElement(i, 1);
			break;
		case lwMPRBase::SAGITTAL:
			result[i] = axis->GetElement(i, 1);
			break;
		}
	}
	return result;
}

vector<double> lwMPRBase::GetHoriVector()
{
	return hv;
}

vector<double> lwMPRBase::GetVertVector()
{
	return vv;
}

void lwMPRBase::SetXAxis(vector<double>& v)
{
	for (int i = 0; i < 3; i++)
	{
		switch (view)
		{
		case lwMPRBase::AXIAL:
			axis->SetElement(i, 0, v[i]);
			break;
		case lwMPRBase::CORONAL:
			axis->SetElement(i, 0, v[i]);
			break;
		case lwMPRBase::SAGITTAL:
			axis->SetElement(i, 2, v[i]);
			break;
		}
	}
}

void lwMPRBase::SetYAxis(vector<double>& v)
{
	for (int i = 0; i < 3; i++)
	{
		switch (view)
		{
		case lwMPRBase::AXIAL:
			axis->SetElement(i, 1, v[i]);
			break;
		case lwMPRBase::CORONAL:
			axis->SetElement(i, 2, v[i]);
			break;
		case lwMPRBase::SAGITTAL:
			axis->SetElement(i, 0, v[i]);
			break;
		}
	}
}

void lwMPRBase::SetZAxis(vector<double>& v)
{
	for (int i = 0; i < 3; i++)
	{
		switch (view)
		{
		case lwMPRBase::AXIAL:
			axis->SetElement(i, 2, v[i]);
			break;
		case lwMPRBase::CORONAL:
			axis->SetElement(i, 1, v[i]);
			break;
		case lwMPRBase::SAGITTAL:
			axis->SetElement(i, 1, v[i]);
			break;
		}
	}
}

void lwMPRBase::SetHoriVector(vector<double>& v)
{
	hv = v;
}

void lwMPRBase::SetVertVector(vector<double>& v)
{
	vv = v;
}

double lwMPRBase::GetXPos()
{
	switch (view)
	{
	case lwMPRBase::AXIAL:
		return xpos;
		break;
	case lwMPRBase::CORONAL:
		return xpos;
		break;
	case lwMPRBase::SAGITTAL:
		return axis->GetElement(2, 3);
		break;
	}
}

double lwMPRBase::GetYPos()
{
	switch (view)
	{
	case lwMPRBase::AXIAL:
		return ypos;
		break;
	case lwMPRBase::CORONAL:
		return axis->GetElement(2, 3);
		break;
	case lwMPRBase::SAGITTAL:
		return xpos;
		break;
	}
}

double lwMPRBase::GetZPos()
{
	switch (view)
	{
	case lwMPRBase::AXIAL:
		return axis->GetElement(2, 3);
		break;
	case lwMPRBase::CORONAL:
		return ypos;
		break;
	case lwMPRBase::SAGITTAL:
		return ypos;
		break;
	}
}

void lwMPRBase::SetXPos(double v)
{
	switch (view)
	{
	case lwMPRBase::AXIAL:
		xpos = v;
		break;
	case lwMPRBase::CORONAL:
		xpos = v;
		break;
	case lwMPRBase::SAGITTAL:
		axis->SetElement(2, 3, v);
		break;
	}
}

void lwMPRBase::SetYPos(double v)
{
	switch (view)
	{
	case lwMPRBase::AXIAL:
		ypos = v;
		break;
	case lwMPRBase::CORONAL:
		axis->SetElement(2, 3, v);
		break;
	case lwMPRBase::SAGITTAL:
		xpos = v;
		break;
	}
}

void lwMPRBase::SetZPos(double v)
{
	switch (view)
	{
	case lwMPRBase::AXIAL:
		axis->SetElement(2, 3, v);
		break;
	case lwMPRBase::CORONAL:
		ypos = v;
		break;
	case lwMPRBase::SAGITTAL:
		ypos = v;
		break;
	}
}
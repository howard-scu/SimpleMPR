#include "lwMPRLogic2.h"

vector<double> crossProduct(vector<double>& a, vector<double>& b)
{
	return vector<double>{
		a[1] * b[2] - a[2] * b[1],
			a[2] * b[0] - a[0] * b[2],
			a[0] * b[1] - a[1] * b[0]};
}

void normalize(vector<double>& v)
{
	double sum = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
	if (sum > 0.0)
	{
		sum = sqrt(sum);
		v[0] /= sum;
		v[1] /= sum;
		v[2] /= sum;
	}
}

lwMPRLogic2::lwMPRLogic2()
{
	axis_matrix = vtkSmartPointer<vtkMatrix4x4>::New();
	axis_matrix->DeepCopy(AXIAL_VIEW);
}


lwMPRLogic2::~lwMPRLogic2()
{
}

void lwMPRLogic2::SetView(MPR_TYPE type)
{
	view_type = type;
}

lwMPRLogic2::MPR_TYPE
lwMPRLogic2::GetView()
{
	return view_type;
}

vector<double> lwMPRLogic2::GetXAxis()
{
	vector<double> result(3, 0.0);
	for (int i = 0; i < 3; i++)
		result[i] = axis_matrix->GetElement(i, 0);
	return result;
}

vector<double> lwMPRLogic2::GetYAxis()
{
	vector<double> result(3, 0.0);
	for (int i = 0; i < 3; i++)
		result[i] = axis_matrix->GetElement(i, 1);
	return result;
}

vector<double> lwMPRLogic2::GetZAxis()
{
	vector<double> result(3, 0.0);
	for (int i = 0; i < 3; i++)
		result[i] = axis_matrix->GetElement(i, 2);
	return result;
}

void lwMPRLogic2::OnXAxisUpdated(vector<double>& v)
{
	for (int i = 0; i < 3; i++)
		axis_matrix->SetElement(i, 0, v[i]);
}

void lwMPRLogic2::OnYAxisUpdated(vector<double>& v)
{
	for (int i = 0; i < 3; i++)
		axis_matrix->SetElement(i, 1, v[i]);
}

void lwMPRLogic2::OnZAxisUpdated(vector<double>& v)
{
	for (int i = 0; i < 3; i++)
		axis_matrix->SetElement(i, 2, v[i]);
}

void lwMPRLogic2::SetXPosition(double v)
{
	xpos = v;
}

void lwMPRLogic2::SetYPosition(double v)
{
	ypos = v;
}

void lwMPRLogic2::SetZPosition(double v)
{
	axis_matrix->SetElement(2, 3, v);
}

void lwMPRLogic2::UpdateVX(vector<double>& v)
{
	/// z轴方向为 (x) x (y)
	/// y轴方向为 (z) x (x)
	/// x轴方向为 (y) x (z)
	normalize(v);
	vx = v;
	vy = crossProduct(GetZAxis(), vx);
}

void lwMPRLogic2::UpdateVY(vector<double>& v)
{
	normalize(v);
	vy = v;
	vx = crossProduct(vy, GetZAxis());
}

vector<double> lwMPRLogic2::GetVX()
{
	return vx;
}

vector<double> lwMPRLogic2::GetVY()
{
	return vy;
}

double lwMPRLogic2::GetXPosition()
{
	return xpos;
}

double lwMPRLogic2::GetYPosition()
{
	return ypos;
}

double lwMPRLogic2::GetZPosition()
{
	return axis_matrix->GetElement(2, 3);
}
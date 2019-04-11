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
	next_viewer = nullptr;
}


lwMPRLogic2::~lwMPRLogic2()
{
	next_viewer = nullptr;
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

void lwMPRLogic2::SetXYPosition(double x, double y)
{
	xpos = x;
	ypos = y;
}

void lwMPRLogic2::SetZPosition(double v)
{
}

void lwMPRLogic2::SetXAxis(vector<double>& v)
{
	/// z轴方向为 (x) x (y)
	/// y轴方向为 (z) x (x)
	/// x轴方向为 (y) x (z)
	normalize(v);
	vx = v;
	vy = crossProduct(GetZAxis(), vx);
}

void lwMPRLogic2::SetYAxis(vector<double>& v)
{
	normalize(v);
	vy = v;
	vx = crossProduct(vy, GetZAxis());
}

void lwMPRLogic2::SetNextViewer(lwMPRLogic2 * viewer)
{
	next_viewer = viewer;
}

void lwMPRLogic2::OnAxisChanged(MPR_TYPE view, vector<double>& v, vector<double>& vy)
{
}

void lwMPRLogic2::OnXPosUpdated(MPR_TYPE view, double pos)
{
}

void lwMPRLogic2::OnYPosUpdated(MPR_TYPE view, double pos)
{
}

void lwMPRLogic2::OnZPosUpdated(MPR_TYPE view, double pos)
{
	switch (view)
	{
	case lwMPRLogic2::AXIAL:
	{
		if (this->GetView() == AXIAL)
		{
			SetZPosition(pos);
		}
		else if (this->GetView() == CORONAL)
		{
			ypos = pos;
		}
		else if (this->GetView() == SAGITTAL)
		{
			xpos = pos;
		}
		break;
	}
	case lwMPRLogic2::CORONAL:
	{
		if (this->GetView() == AXIAL)
		{
			SetZPosition(pos);
		}
		else if (this->GetView() == CORONAL)
		{
			ypos = pos;
		}
		else if (this->GetView() == SAGITTAL)
		{
			xpos = pos;
		}
		break;
	}
	case lwMPRLogic2::SAGITTAL:
	{
		if (this->GetView() == AXIAL)
		{
			SetZPosition(pos);
		}
		else if (this->GetView() == CORONAL)
		{
			ypos = pos;
		}
		else if (this->GetView() == SAGITTAL)
		{
			xpos = pos;
		}
		break;
	}
	case lwMPRLogic2::OBLIQUE:
		break;
	}
}


////void lwMPRLogic2::SetXAxis(vector<double>& v)
////{
////}
////
////void lwMPRLogic2::SetYAxis(vector<double>& v)
////{
////}
////
////void lwMPRLogic2::SetZAxis(vector<double>& v)
////{
////}
//
//void lwMPRLogic2::OnXAxisUpdated(MPR_TYPE view, vector<double>& v)
//{
//	for (int i = 0; i < 3; i++)
//		axis_matrix->SetElement(i, 0, v[i]);
//}
//
//void lwMPRLogic2::OnYAxisUpdated(MPR_TYPE view, vector<double>& v)
//{
//	for (int i = 0; i < 3; i++)
//		axis_matrix->SetElement(i, 1, v[i]);
//}
//
//void lwMPRLogic2::OnZAxisUpdated(MPR_TYPE view, vector<double>& v)
//{
//	for (int i = 0; i < 3; i++)
//		axis_matrix->SetElement(i, 2, v[i]);
//}
//
//void lwMPRLogic2::OnXPosUpdated(MPR_TYPE view, double pos)
//{
//	cout << "x " << view << " : " << pos << endl;
//}
//
//void lwMPRLogic2::OnYPosUpdated(MPR_TYPE view, double pos)
//{
//	cout << "y " << view << " : " << pos << endl;
//}
//
//void lwMPRLogic2::OnZPosUpdated(MPR_TYPE view, double pos)
//{
//	cout << "z " << view << " : " << pos << endl;
//}
//
//void lwMPRLogic2::SetXPosition(double v)
//{
//	xpos = v;
//}
//
//void lwMPRLogic2::SetYPosition(double v)
//{
//	ypos = v;
//}
//
//void lwMPRLogic2::SetZPosition(double v)
//{
//	axis_matrix->SetElement(2, 3, v);
//}
//
//void lwMPRLogic2::UpdateVX(vector<double>& v)
//{
//	/// z轴方向为 (x) x (y)
//	/// y轴方向为 (z) x (x)
//	/// x轴方向为 (y) x (z)
//	normalize(v);
//	vx = v;
//	vy = crossProduct(GetZAxis(), vx);
//}
//
//void lwMPRLogic2::UpdateVY(vector<double>& v)
//{
//	normalize(v);
//	vy = v;
//	vx = crossProduct(vy, GetZAxis());
//}
//
//vector<double> lwMPRLogic2::GetVX()
//{
//	return vx;
//}
//
//vector<double> lwMPRLogic2::GetVY()
//{
//	return vy;
//}
//
//void lwMPRLogic2::Connect(lwMPRLogic2 * viewer)
//{
//
//}
//


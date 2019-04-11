#ifndef _LW_MPR_BASE_H
#define _LW_MPR_BASE_H
#include <vector>
#include <memory>
#include <iostream>
#include <list>

#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>

using namespace std;

class lwMPRBase
{
public:
	lwMPRBase();
	~lwMPRBase();
	enum MPR_TYPE
	{
		AXIAL = 1,
		CORONAL = 2,
		SAGITTAL = 4,
		OBLIQUE
	};

	void			SetView(MPR_TYPE type);
	MPR_TYPE		GetView();

	vector<double>	GetXAxis();
	vector<double>	GetYAxis();
	vector<double>	GetZAxis();

	vector<double>	GetHoriVector();
	vector<double>	GetVertVector();

	double			GetXPos();
	double			GetYPos();
	double			GetZPos();

	//protected:
	void			SetXAxis(vector<double>& v);
	void			SetYAxis(vector<double>& v);
	void			SetZAxis(vector<double>& v);

	void			SetHoriVector(vector<double>& v);
	void			SetVertVector(vector<double>& v);

	void			SetXPos(double v);
	void			SetYPos(double v);
	void			SetZPos(double v);


private:
	vtkSmartPointer<vtkMatrix4x4>			axis;
	MPR_TYPE								view{ AXIAL };
	double			xpos{ 0 };
	double			ypos{ 0 };
	double			zpos{ 0 };

	vector<double>	hv{ 1,0,0 };
	vector<double>	vv{ 0,1,0 };

	const double AXIAL_VIEW[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	const double CORONAL_VIEW[16] = {
		1, 0, 0, 0,
		0, 0, 1, 0,
		0, 1, 0, 0,
		0, 0, 0, 1 };
	const double SAGITTAL_VIEW[16] = {
		0, 0, 1, 0,
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 1 };
};

#endif // !_LW_MPR_BASE_H

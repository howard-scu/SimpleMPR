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
	};

	void			SetView(MPR_TYPE type);
	MPR_TYPE		GetView();

protected:
	double GetXPos() { return xpos; }
	double GetYPos() { return ypos; }
	double GetZPos() { return zpos; }

	void SetXPos(double mx);
	void SetYPos(double my);
	void SetZPos(double mz);

	double GetAlpha() { return alpha; }
	double GetBeta() { return beta; }
	double GetGamma() { return gamma; }

	void SetAlpha(double a);
	void SetBeta(double b);
	void SetGamma(double g);

protected:
	vtkSmartPointer<vtkMatrix4x4>			view_mat;

private:
	void Init();
	MPR_TYPE								view{ AXIAL };

	double			xpos{ 0 };
	double			ypos{ 0 };
	double			zpos{ 0 };

	double			alpha{ 0 };			// ÈÆxÖáÐý×ª½Ç
	double			beta{ 0 };			// ÈÆyÖáÐý×ª½Ç
	double			gamma{ 0 };			// ÈÆzÖáÐý×ª½Ç

	const double AXIAL_VIEW[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	const double CORONAL_VIEW[16] = {
		1, 0, 0, 0,
		0, 0, 1, 0,
		0, -1, 0, 0,
		0, 0, 0, 1 };
	const double SAGITTAL_VIEW[16] = {
		0, 0, 1, 0,
		-1, 0, 0, 0,
		0, -1, 0, 0,
		0, 0, 0, 1 };
};

#endif // !_LW_MPR_BASE_H

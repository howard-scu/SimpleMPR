#ifndef _LW_MPR_LOGIC_H
#define _LW_MPR_LOGIC_H

#include <vector>
#include <memory>
#include <iostream>
#include <list>

#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>

using namespace std;

class lwMPRLogic
{
public:

	lwMPRLogic();
	~lwMPRLogic();

	enum MPR_TYPE
	{
		AXIAL,
		CORONAL,
		SAGITTAL,
		OBLIQUE
	};

	void SetView(MPR_TYPE type);
	MPR_TYPE GetView();

	void	SyncView(lwMPRLogic* viewer);
	
	vector<double>	GetXAxis();
	vector<double>	GetYAxis();
	vector<double>	GetZAxis();
	vector<double>	GetPosition();

	void	UpdateXAxis(vector<double>& vec);
	void	UpdateYAxis(vector<double>& vec);
	void	UpdateZAxis(vector<double>& vec);
	void	OnAxisChanged(vtkSmartPointer<vtkMatrix4x4> matrix);

	void	OnPositionChanged(vector<double>& vec);
	virtual void Render() = 0;

protected:
	vtkSmartPointer<vtkMatrix4x4>			view_matrix;
	vtkSmartPointer<vtkMatrix4x4>			axis_matrix;
	MPR_TYPE								view_type;
	vector<double>							position{0,0,0};

private:
	lwMPRLogic*								next_viewer;
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

#endif // !_LW_MPR_LOGIC_H

#ifndef _LW_MPR_LOGIC_H
#define _LW_MPR_LOGIC_H

#include <vector>
#include <memory>
#include <iostream>
#include <list>

#include <vtkSmartPointer.h>
#include <vtkImageReslice.h>
#include <vtkImageData.h>
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

	/* 设置方向 */
	void SetView(MPR_TYPE type);

	/* 设置同步窗口 */
	void SyncView(lwMPRLogic* viewer);
	void OnAxisMatrixChanged(vtkSmartPointer<vtkMatrix4x4> matrix);

	void UpdateXAxis(vector<double>& vec);
	void UpdateYAxis(vector<double>& vec);
	void UpdateZAxis(vector<double>& vec);
	void UpdateCenter(vector<double>& vec);

	vector<double> GetXAxis();
	vector<double> GetYAxis();
	vector<double> GetZAxis();
	vector<double> GetCenter();

	void Render();

private:
	vtkSmartPointer<vtkMatrix4x4>			view_matrix;
	vtkSmartPointer<vtkMatrix4x4>			axis_matrix;
	vtkSmartPointer<vtkMatrix4x4>			trans_matrix;
	vector<double>							oblique_axis;
	lwMPRLogic*						next_viewer;

	MPR_TYPE								view;
	const double AXIAL_VIEW[16] = { 1, 0, 0, 0,0, 1, 0, 0,0, 0, 1, 0,0, 0, 0, 1 };
	const double CORONAL_VIEW[16] = { 1, 0, 0, 0,0, 0, 1, 0,0, 1, 0, 0,0, 0, 0, 1 };
	const double SAGITTAL_VIEW[16] = { 0, 0, 1, 0,1, 0, 0, 0,0, 1, 0, 0,0, 0, 0, 1 };
};

#endif // !_LW_MPR_LOGIC_H

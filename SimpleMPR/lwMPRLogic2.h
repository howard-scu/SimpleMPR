#ifndef _LW_MPR_LOGIC2_H
#define _LW_MPR_LOGIC2_H

#include <vector>
#include <memory>
#include <iostream>
#include <list>

#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>

using namespace std;

// 向量归一化操作
static void normalize(vector<double>& v);

// 向量叉乘操作
static vector<double> crossProduct(vector<double>& a, vector<double>& b);

// 用于实现MPR逻辑
class lwMPRLogic2
{
public:
	lwMPRLogic2();
	~lwMPRLogic2();

	enum MPR_TYPE
	{
		AXIAL,
		CORONAL,
		SAGITTAL,
		OBLIQUE
	};

	// 设置显示方向
	// TODO:禁止过程中修改
	void SetView(MPR_TYPE type);
	MPR_TYPE GetView();

	// 当前重采样的方向向量
	//  x1 x2 x3 0
	//  y1 y2 y3 0
	//  z1 z2 z3 cz
	//  0  0  0  1
	// 输入图像初始化对齐图像中心
	//		1.x轴方向为(x1,y1,z1)
	//		2.y轴方向为(x2,y2,z2)
	//		3.z轴方向为(x3,y3,z3)
	//		4.旋转中心为(0,0,cz)
	vector<double>	GetXAxis();
	vector<double>	GetYAxis();
	vector<double>	GetZAxis();

	// 同步视图中vx/vy改变时
	// 回调函数，用来改变当前视图
	void			OnXAxisUpdated(vector<double>& v);
	void			OnYAxisUpdated(vector<double>& v);
	void			OnZAxisUpdated(vector<double>& v);

	// 用于设置/获取十字光标位置
	double			GetXPosition();
	double			GetYPosition();
	void			SetXPosition(double v);
	void			SetYPosition(double v);
	
	// 用于改变当前切片
	double			GetZPosition();
	void			SetZPosition(double v);

	// 用于改变当前切片
	void			UpdateVX(vector<double>& v);
	void			UpdateVY(vector<double>& v);
	vector<double>	GetVX();
	vector<double>	GetVY();

private:
	// 当前十字交叉点位置
	double	xpos{ 0 };
	double	ypos{ 0 };

	// 当前十字交叉向量
	vector<double> vx{ 1,0,0 };
	vector<double> vy{ 0,1,0 };

	vtkSmartPointer<vtkMatrix4x4>			axis_matrix;
	MPR_TYPE								view_type{ AXIAL };
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

#endif // !_LW_MPR_LOGIC2_H

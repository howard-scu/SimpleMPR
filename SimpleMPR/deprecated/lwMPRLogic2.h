#ifndef _LW_MPR_LOGIC2_H
#define _LW_MPR_LOGIC2_H

#include <vector>
#include <memory>
#include <iostream>
#include <list>

#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>
#include <boost/signals2.hpp>

using namespace std;

// 向量归一化操作
static void normalize(vector<double>& v);

// 向量叉乘操作
static vector<double> crossProduct(vector<double>& a, vector<double>& b);
//lwMPRLogic2
//// 主动
//- SetXYPos(double x,double y)			/// 鼠标拖动中心点
//- SetZSlice(double z)					/// 鼠标滚轮 
//- SetVX(double* vx)					/// 鼠标拖动十字线转动
//- SetVY(double* vy)					/// 鼠标拖动十字线转动
//
//// 被动
//- OnXPosChanged(double x)					/// 横轴坐标响应改变
//- OnYPosChanged(double y)					/// 纵轴坐标响应改变
//- OnAxisChanged(double* vx,double vy)		/// 横轴坐标改变
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
	double			GetXPosition();
	double			GetYPosition();
	double			GetZPosition();
	
	// 用于设置十字光标位置
	void			SetXYPosition(double x,double y);
	
	// 用于改变当前切片
	void			SetZPosition(double v);

	// 用于改变当前切片
	void			SetXAxis(vector<double>& v);
	void			SetYAxis(vector<double>& v);

	void			SetNextViewer(lwMPRLogic2* viewer);
private:
	boost::signals2::signal<void(MPR_TYPE, vector<double>&)> vx_update_sig;
	boost::signals2::signal<void(MPR_TYPE, vector<double>&)> vy_update_sig;
	boost::signals2::signal<void(MPR_TYPE, double)> xpos_update_sig;
	boost::signals2::signal<void(MPR_TYPE, double)> ypos_update_sig;
	boost::signals2::signal<void(MPR_TYPE, double)> zpos_update_sig;

	// 同步视图中vx/vy改变时
	// 回调函数，用来改变当前视图
	void			OnAxisChanged(MPR_TYPE view, vector<double>& vx, vector<double>& vy);
	void			OnXPosUpdated(MPR_TYPE view, double pos);
	void			OnYPosUpdated(MPR_TYPE view, double pos);
	void			OnZPosUpdated(MPR_TYPE view, double pos);

	lwMPRLogic2*	next_viewer;

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




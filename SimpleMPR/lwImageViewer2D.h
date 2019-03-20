#ifndef _LW_IMAGE_VIEWER_2D_H
#define _LW_IMAGE_VIEWER_2D_H

#include <vtkSmartPointer.h>
#include <vtkImageReslice.h>
#include <vtkImageData.h>
#include <vtkMatrix4x4.h>
#include <vtkLookupTable.h>
#include <vtkImageMapToColors.h>

#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>

#include <vtkActor.h>
#include <vtkLineSource.h>
#include <vtkCornerAnnotation.h>
#include <vtkPolyDataMapper.h>

#include "lwDef.h"

class vtkImageInteractionCallback;

class lwImageViewer2D
{
public:
	lwImageViewer2D();
	~lwImageViewer2D();

	void SetInputImage(vtkSmartPointer<vtkImageData> input);
	void SetOrientation(ORIENTATION_TYPE orient);
	ORIENTATION_TYPE GetOrientation() { return _orientation; }
	void Render();

	double* GetPosition()
	{
		return _cursorPosition;
	}

	// 窗宽窗位
	void SetColorWindow(int win);
	void SetColorLevel(int level);
	int	 GetColorWindow();
	int  GetColorLevel();

	// 显示窗口大小
	void SetWindowSize(int width, int height);
	int* GetWindowSize();

	// 设置十字光标位置
	void UpdateCursorPosition(int* pos);

	// 显示十字光标
	void SetShowCursor(bool flag);

	// 图像充满窗口
	void SetShowFullWindow(bool flag);

	// 显示图像方位信息
	void SetShowOrientationAnnotation(bool flag);

	// 显示Dicom信息
	void SetDicomInfoAnnotation(vtkCornerAnnotation::TextPosition i, const char* info);

	// 交互设置
	void SetLeftButtonInteractionStyle(INTERACTION_TYPE& type);
	void SetRightButtonInteractionStyle(INTERACTION_TYPE& type);
	void SetMiddleButtonInteractionStyle(INTERACTION_TYPE& type);
	void SetWheelInteractionStyle(INTERACTION_TYPE& type);
	void UpdatePosition(double* pos);
	void SetInteractor(vtkSmartPointer<vtkRenderWindowInteractor> interactor);

	void LinkNextViewer(lwImageViewer2D* w);
private:
	int							_color_window;
	int							_color_level;
	ORIENTATION_TYPE			_orientation;
	double						_center[3];
	bool						_firstRender;
	double						_cursorPosition[3];
	int							_currentSlice;
	double						_scale;

	vtkSmartPointer<vtkImageData>			_image;
	vtkSmartPointer<vtkMatrix4x4>			_resliceAxes;
	vtkSmartPointer<vtkImageReslice>		_reslice;
	vtkSmartPointer<vtkLookupTable>			_table;
	vtkSmartPointer<vtkImageMapToColors>	_color;
	vtkSmartPointer<vtkImageActor>			_actor;
	vtkSmartPointer<vtkRenderer>			_renderer;
	vtkSmartPointer<vtkRenderWindow>		_window;
	vtkSmartPointer<vtkRenderWindowInteractor>			_interactor;
	vtkSmartPointer<vtkInteractorStyleImage>			_imageStyle;
	vtkSmartPointer<vtkImageInteractionCallback>		_callback;

	vtkSmartPointer<vtkActor>						_horizontalline_actor;
	vtkSmartPointer<vtkActor>						_verticalline_actor;
	vtkSmartPointer<vtkLineSource>					_horizontalline_source;
	vtkSmartPointer<vtkLineSource>					_verticalline_source;
	vtkSmartPointer<vtkPolyDataMapper>				_horizontalline_mappper;
	vtkSmartPointer<vtkPolyDataMapper>				_verticalline_mappper;
	vtkSmartPointer<vtkCornerAnnotation>			_corner_annotation;
	vtkSmartPointer<vtkCornerAnnotation>			_orientation_annotation;

	bool IsMaster()
	{
		lwImageViewer2D* pWin = this;
		unsigned int max = 0;
		do
		{
			if (max < pWin->wid)
			{
				max = pWin->wid;
			}
			pWin = pWin->next;
		} while (pWin && pWin != this);

		return max == wid;
	}

	unsigned int LeftButtonInteractionStyle;
	unsigned int RightButtonInteractionStyle;
	unsigned int MiddleButtonInteractionStyle;
	unsigned int WheelInteractionStyle;

	void	InitCursor(ORIENTATION_TYPE type);

	static unsigned int id;
	unsigned int wid;
	lwImageViewer2D* next{ nullptr };
	unsigned int val{ 0 };
};

#endif // !_LW_IMAGE_VIEWER_2D_H



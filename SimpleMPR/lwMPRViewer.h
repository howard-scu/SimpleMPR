#ifndef _LW_MPR_IMAGE_VIEWER_H
#define _LW_MPR_IMAGE_VIEWER_H

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
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkRenderer.h>

#include <vtkActor.h>
#include <vtkLineSource.h>
#include <vtkCornerAnnotation.h>
#include <vtkPolyDataMapper.h>
#include <vtkInteractorStyleUser.h>
#include <vtkCellPicker.h>
#include "lwMPRLogic.h"
#include "lwMPRCallback.h"

class lwMPRViewer :public lwMPRLogic
{
public:
	lwMPRViewer();
	~lwMPRViewer();

	void SetInput(vtkSmartPointer<vtkImageData> input);
	vtkSmartPointer<vtkImageData> GetInput() {return image;}
	void Render();
	void UpdateCursor();

private:
	void InitCursor();
	//void UpdateCursor();

	vtkSmartPointer<vtkImageData>			image;
	vtkSmartPointer<vtkMatrix4x4>			resliceAxes;
	vtkSmartPointer<vtkImageReslice>		reslice;
	vtkSmartPointer<vtkLookupTable>			table;
	vtkSmartPointer<vtkImageMapToColors>	color;
	vtkSmartPointer<vtkImageActor>			actor;
	vtkSmartPointer<vtkRenderer>			renderer;
	vtkSmartPointer<vtkRenderWindow>		window;

	vtkSmartPointer<vtkCellPicker>			_cursor_picker;
	vtkSmartPointer<vtkCellPicker>			_vert_picker;
	vtkSmartPointer<vtkCellPicker>			_hori_picker;

	vtkSmartPointer<vtkActor>						_horizontalline_actor;
	vtkSmartPointer<vtkActor>						_verticalline_actor;
	vtkSmartPointer<vtkLineSource>					_horizontalline_source;
	vtkSmartPointer<vtkLineSource>					_verticalline_source;
	vtkSmartPointer<vtkPolyDataMapper>				_horizontalline_mappper;
	vtkSmartPointer<vtkPolyDataMapper>				_verticalline_mappper;

	vtkSmartPointer<vtkRenderWindowInteractor>			interactor;
	vtkSmartPointer<vtkInteractorStyleImage>			imageStyle;
	vtkSmartPointer<lwMPRCallback>						callback;
	bool	render_flag{ false };
	double	angle{ 0 };
};

#endif // !_LW_MPR_IMAGE_VIEWER2_H

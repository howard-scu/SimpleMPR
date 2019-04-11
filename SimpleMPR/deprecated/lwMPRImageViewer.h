#ifndef _LW_MPR_IMAGE_VIEWER_H
#define _LW_MPR_IMAGE_VIEWER_H

#include "lwMPRLogic.h"
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

#include "lwMPRImageInteractionCallback.h"

class lwMPRImageViewer :
	public lwMPRLogic
{
public:
	lwMPRImageViewer();
	~lwMPRImageViewer();
	void SetInput(vtkSmartPointer<vtkImageData> input);
	vtkSmartPointer<vtkImageData>	GetInput();
	vtkSmartPointer<vtkImageActor>	GetImageActor();
	void Render();

private:
	void InitCursor();
	void UpdateCursor();

	vtkSmartPointer<vtkImageData>			image;
	vtkSmartPointer<vtkMatrix4x4>			resliceAxes;
	vtkSmartPointer<vtkImageReslice>		reslice;
	vtkSmartPointer<vtkLookupTable>			table;
	vtkSmartPointer<vtkImageMapToColors>	color;
	vtkSmartPointer<vtkImageActor>			actor;
	vtkSmartPointer<vtkRenderer>			renderer;
	vtkSmartPointer<vtkRenderWindow>		window;

	vtkSmartPointer<vtkCellPicker>			_horizontalline_picker;
	vtkSmartPointer<vtkCellPicker>			_verticalline_picker;

	vtkSmartPointer<vtkActor>						_horizontalline_actor;
	vtkSmartPointer<vtkActor>						_verticalline_actor;
	vtkSmartPointer<vtkLineSource>					_horizontalline_source;
	vtkSmartPointer<vtkLineSource>					_verticalline_source;
	vtkSmartPointer<vtkPolyDataMapper>				_horizontalline_mappper;
	vtkSmartPointer<vtkPolyDataMapper>				_verticalline_mappper;

	vtkSmartPointer<vtkRenderWindowInteractor>			interactor;
	vtkSmartPointer<vtkInteractorStyleImage>			imageStyle;
	vtkSmartPointer<lwMPRImageInteractionCallback>		callback;
	bool	render_flag{ false };
};

#endif // !_LW_MPR_IMAGE_VIEWER_H

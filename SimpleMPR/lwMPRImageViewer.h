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
#include "lwMPRImageInteractionCallback.h"
#include <vtkInteractorStyleUser.h>
class lwMPRImageViewer :
	public lwMPRLogic
{
public:
	lwMPRImageViewer();
	~lwMPRImageViewer();
	void SetInput(vtkSmartPointer<vtkImageData> input);
	vtkSmartPointer<vtkImageData> GetInput();
	void Render();
private:
	vtkSmartPointer<vtkImageData>			image;
	vtkSmartPointer<vtkMatrix4x4>			resliceAxes;
	vtkSmartPointer<vtkImageReslice>		reslice;
	vtkSmartPointer<vtkLookupTable>			table;
	vtkSmartPointer<vtkImageMapToColors>	color;
	vtkSmartPointer<vtkImageActor>			actor;
	vtkSmartPointer<vtkRenderer>			renderer;
	vtkSmartPointer<vtkRenderWindow>		window;
	vtkSmartPointer<vtkRenderWindowInteractor>			interactor;
	vtkSmartPointer<vtkInteractorStyleUser>	imageStyle;
	vtkSmartPointer<lwMPRImageInteractionCallback>		callback;
	bool	render_flag{ false };
};

#endif // !_LW_MPR_IMAGE_VIEWER_H

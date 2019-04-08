#ifndef _LW_MPR_IMAGE_INTERACTION_CALLBACK_H
#define _LW_MPR_IMAGE_INTERACTION_CALLBACK_H

#include <vtkSmartPointer.h>
#include <vtkCommand.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPropPicker.h>
#include <vtkImageData.h>
#include <vtkObjectFactory.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCellPicker.h>
#include <vector>

using namespace std;

class lwMPRImageViewer;

class lwMPRImageInteractionCallback : public vtkCommand
{
public:
	vtkTypeMacro(lwMPRImageInteractionCallback, vtkCommand);
	static lwMPRImageInteractionCallback *New();
	void Execute(vtkObject* caller, unsigned long eventId, void* callData);
	void SetRenderer(vtkSmartPointer<vtkRenderer> ren);
	void SetViewer(lwMPRImageViewer* view);
	void SetInput(vtkSmartPointer<vtkImageData> input);
	void SetHoriPicker(vtkSmartPointer<vtkCellPicker> picker);
	void SetVertPicker(vtkSmartPointer<vtkCellPicker> picker);

protected:
	lwMPRImageInteractionCallback();
	~lwMPRImageInteractionCallback();

private:
	vector<double>	MousePick(vtkRenderWindowInteractor* iren);
	vtkSmartPointer<vtkCellPicker>			_horizontalline_picker;
	vtkSmartPointer<vtkCellPicker>			_verticalline_picker;
	vtkSmartPointer<vtkPropPicker>	picker;
	vtkSmartPointer<vtkRenderer>	renderer;
	vtkSmartPointer<vtkImageData>	image;
	lwMPRImageViewer*				viewer;
	bool							lp{ false };
	int								hflag{ 0 };
	int								vflag{ 0 };
};

#endif // !_LW_MPR_IMAGE_INTERACTION_CALLBACK_H

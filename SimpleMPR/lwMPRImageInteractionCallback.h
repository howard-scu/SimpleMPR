#ifndef _LW_MPR_IMAGE_INTERACTION_CALLBACK_H
#define _LW_MPR_IMAGE_INTERACTION_CALLBACK_H

#include <vtkSmartPointer.h>
#include <vtkCommand.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPropPicker.h>
#include <vtkImageData.h>
#include <vtkObjectFactory.h>
#include <vtkRenderer.h>

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

protected:
	lwMPRImageInteractionCallback();
	~lwMPRImageInteractionCallback();

private:
	vtkSmartPointer<vtkPropPicker>	picker;
	vtkSmartPointer<vtkRenderer>	renderer;
	vtkSmartPointer<vtkImageData>	image;
	lwMPRImageViewer*				viewer;
	bool							lp{ false };
};

#endif // !_LW_MPR_IMAGE_INTERACTION_CALLBACK_H

#ifndef _LW_MPR_IMAGE_INTERACTION_CALLBACK_H
#define _LW_MPR_IMAGE_INTERACTION_CALLBACK_H

#include <vtkSmartPointer.h>
#include <vtkCommand.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPropPicker.h>
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

protected:
	lwMPRImageInteractionCallback();
	~lwMPRImageInteractionCallback();

private:
	vtkSmartPointer<vtkPropPicker>	picker;
	vtkSmartPointer<vtkRenderer>	renderer;
	lwMPRImageViewer*				viewer;
	bool							lp{false};
	int		extent[6];
	double	spacing[3];
	double	origin[3];
	double	center[3];
};

#endif // !_LW_MPR_IMAGE_INTERACTION_CALLBACK_H

#ifndef _LW_MPR_CALLBACK_H
#define _LW_MPR_CALLBACK_H

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

class lwMPRViewer;

class lwMPRCallback : public vtkCommand
{
public:
	vtkTypeMacro(lwMPRCallback, vtkCommand);
	static lwMPRCallback *New();
	void Execute(vtkObject* caller, unsigned long eventId, void* callData);
	void SetViewer(lwMPRViewer* mv);
	void SetRenderer(vtkSmartPointer<vtkRenderer> mr) { renderer = mr; }
	void SetHoriPicker(vtkSmartPointer<vtkCellPicker> picker) { _hori_picker = picker; }
	void SetVertPicker(vtkSmartPointer<vtkCellPicker> picker) { _vert_picker = picker; }

protected:
	lwMPRCallback();
	~lwMPRCallback();

private:
	vtkSmartPointer<vtkCellPicker>			_vert_picker;
	vtkSmartPointer<vtkCellPicker>			_hori_picker;
	vtkSmartPointer<vtkPropPicker>			point_picker;
	vtkSmartPointer<vtkRenderer>	renderer;
	double							spacing[3];
	lwMPRViewer*					viewer;
	bool	lp{ false };
	int		hflag{ 0 };
	int		vflag{ 0 };
};
#endif // !_LW_MPR_CALLBACK_H


#include <vtkAutoInit.h>
#include <vtkMetaImageReader.h>
#include <vtkDICOMImageReader.h>
#include "lwMPRViewer.h"


VTK_MODULE_INIT(vtkRenderingVolumeOpenGL);
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType)

void main()
{
	auto reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	reader->SetDirectoryName("E:\\CarotidAnalyze\\VirtualEndoscopy\\data\\Head");
	reader->Update();

	shared_ptr<lwMPRViewer> viewer1 = make_shared<lwMPRViewer>();
	shared_ptr<lwMPRViewer> viewer2 = make_shared<lwMPRViewer>();
	shared_ptr<lwMPRViewer> viewer3 = make_shared<lwMPRViewer>();

	viewer1->SetView(lwMPRLogic::AXIAL);
	viewer2->SetView(lwMPRLogic::CORONAL);
	viewer3->SetView(lwMPRLogic::SAGITTAL);

	viewer1->SyncViewer(viewer2.get());
	viewer2->SyncViewer(viewer3.get());
	viewer3->SyncViewer(viewer1.get());

	viewer1->SetInput(reader->GetOutput());
	viewer2->SetInput(reader->GetOutput());
	viewer3->SetInput(reader->GetOutput());

	viewer1->Render();
	viewer2->Render();
	viewer3->Render();
}

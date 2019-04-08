#define CATCH_CONFIG_MAIN
#include <catch2\catch.hpp>
#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingVolumeOpenGL);
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType)

#include "lwMPRImageViewer.h"
#include <vtkSmartPointer.h>
#include <vtkMetaImageReader.h>

using Catch::Matchers::Equals;


TEST_CASE("Test for mpr viewer", "[single-file]")
{
	auto reader = vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName("c:\\0.mha");
	reader->Update();

	shared_ptr<lwMPRImageViewer> viewer1 = make_shared<lwMPRImageViewer>();
	shared_ptr<lwMPRImageViewer> viewer2 = make_shared<lwMPRImageViewer>();
	shared_ptr<lwMPRImageViewer> viewer3 = make_shared<lwMPRImageViewer>();

	viewer1->SetView(lwMPRLogic::AXIAL);
	viewer2->SetView(lwMPRLogic::CORONAL);
	viewer3->SetView(lwMPRLogic::SAGITTAL);

	viewer1->SyncView(viewer2.get());
	viewer2->SyncView(viewer3.get());
	viewer3->SyncView(viewer1.get());

	viewer1->SetInput(reader->GetOutput());
	viewer2->SetInput(reader->GetOutput());
	viewer3->SetInput(reader->GetOutput());

	viewer1->Render();
	viewer2->Render();
	viewer3->Render();
}



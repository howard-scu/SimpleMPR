#include "qtmipdemo.h"
#include <QtWidgets/QApplication>
#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingVolumeOpenGL);
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType)

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtMipDemo w;
	w.show();
	return a.exec();
}

#ifndef _LW_DEF_H
#define _LW_DEF_H

#include <iostream>

using namespace std;

enum ORIENTATION_TYPE
{
	AXIAL,
	CORONAL,
	SAGITTAL
};

enum INTERACTION_TYPE
{
	NO_INTERACTION,
	SELECT_INTERACTION,
	WINDOW_LEVEL_INTERACTION,
	FULL_PAGE_INTERACTION,
	MEASURE_INTERACTION,
	ZOOM_INTERACTION
};

const double AxialElements[16] =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

const double CoronalElements[16] =
{
	1, 0, 0, 0,
	0, 0, 1, 0,
	0, 1, 0, 0,
	0, 0, 0, 1
};

const double SagittalElements[16] =
{
	0, 0, 1, 0,
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, 1
};


//template<class T>
//void print3(const char* desc, T* pt)
//{
//	cout << desc << endl;
//	cout << (pt)[0] << ", " << (pt)[1] << ", " << (pt)[2] << endl;
//}
//
//template<class T>
//void print6(const char* desc, T* pt)
//{
//	cout << desc << endl;
//	cout << (pt)[0] << ", " << (pt)[1] << endl;
//	cout << (pt)[2] << ", " << (pt)[3] << endl;
//	cout << (pt)[4] << ", " << (pt)[5] << endl;
//}

#endif // !_LW_IMAGE_VIEWER_2D_H


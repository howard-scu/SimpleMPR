#include "lwMPRLogic.h"
#include "lwUtils.h"

lwMPRLogic::lwMPRLogic()
{
	next = nullptr;
}

lwMPRLogic::~lwMPRLogic()
{
	next = nullptr;
}

void lwMPRLogic::SyncViewer(lwMPRLogic * viewer)
{
	next = viewer;
}

void lwMPRLogic::UpdateSlice(double nslice)
{
	switch (this->GetView())
	{
	case lwMPRBase::AXIAL:
		this->SetZPos(nslice);
		break;
	case lwMPRBase::CORONAL:
		this->SetYPos(nslice);
		break;
	case lwMPRBase::SAGITTAL:
		this->SetXPos(nslice);
		break;
	}
	if (next)
	{
		if (!slice_connection.connected())
		{
			slice_connection = slice_signal.connect(
				boost::bind(&lwMPRLogic::slice_update_slot, next, _1, _2));
		}
		slice_signal(this->GetView(), nslice);
	}
}

void lwMPRLogic::UpdatePosition(double x, double y)
{
	switch (this->GetView())
	{
	case lwMPRBase::AXIAL:
		this->SetXPos(x);
		this->SetYPos(y);
		break;
	case lwMPRBase::CORONAL:
		this->SetXPos(x);
		this->SetZPos(y);
		break;
	case lwMPRBase::SAGITTAL:
		this->SetYPos(x);
		this->SetZPos(y);
		break;
	}
	if (next)
	{
		if (!position_connection.connected())
		{
			position_connection = position_signal.connect(
				boost::bind(&lwMPRLogic::position_update_slot, next, _1, _2, _3));
		}
		position_signal(this->GetView(), x, y);
	}
}

void lwMPRLogic::UpdateHoriVector(vector<double>& v)
{
	// xyz坐标系如图：
	//		  y+|
	//			|
	//			|
	//			|__________ x+
	//		   /
	//		  /
	//	   z+/
	// 1.AXIAL
	//   - 视图对应XY平面
	//   - x轴方向确定，则y轴方向由Z^X决定
	//   - y轴方向确定，则x轴方向由Y^Z决定
	// 2.CORONAL  
	//   - 视图对应XZ平面
	//   - x轴方向确定，则z轴方向由X^Y决定
	//   - z轴方向确定，则x轴方向由Y^Z决定
	// 3.SAGITTAL 
	//	 - 视图对应YZ平面
	//   - y轴方向确定，则z轴方向由X^Y决定
	//   - z轴方向确定，则y轴方向由Z^X决定
	lwUtils::Normalize(v);
	vector<double> v1;
	switch (this->GetView())
	{
	case lwMPRBase::AXIAL:
		v1 = lwUtils::CrossProduct(this->GetZAxis(), v);
		break;
	case lwMPRBase::CORONAL:
		v1 = lwUtils::CrossProduct(v, this->GetYAxis());
		break;
	case lwMPRBase::SAGITTAL:
		v1 = lwUtils::CrossProduct(this->GetXAxis(), v);
		break;
	}
	this->SetHoriVector(v);
	this->SetVertVector(v1);

	if (next)
	{
		if (!vector_connection.connected())
		{
			vector_connection = vector_signal.connect(
				boost::bind(&lwMPRLogic::vector_update_slot, next, _1, _2, _3));
		}
		vector_signal(this->GetView(), v, v1);
	}
}

void lwMPRLogic::UpdateVertVector(vector<double>& v)
{
	lwUtils::Normalize(v);
	vector<double> v1;
	switch (this->GetView())
	{
	case lwMPRBase::AXIAL:
		v1 = lwUtils::CrossProduct(v, this->GetZAxis());
		break;
	case lwMPRBase::CORONAL:
		v1 = lwUtils::CrossProduct(this->GetYAxis(), v);
		break;
	case lwMPRBase::SAGITTAL:
		v1 = lwUtils::CrossProduct(v, this->GetXAxis());
		break;
	}
	this->SetHoriVector(v1);
	this->SetVertVector(v);
	if (next)
	{
		if (!vector_connection.connected())
		{
			vector_connection = vector_signal.connect(
				boost::bind(&lwMPRLogic::vector_update_slot, next, _1, _2, _3));
		}
		vector_signal(this->GetView(), v1, v);
	}
}

void lwMPRLogic::slice_update_slot(MPR_TYPE view, double nslice)
{
	switch (view)
	{
	case lwMPRBase::AXIAL:
		this->SetZPos(nslice);
		break;
	case lwMPRBase::CORONAL:
		this->SetYPos(nslice);
		break;
	case lwMPRBase::SAGITTAL:
		this->SetXPos(nslice);
		break;
	}
}

void lwMPRLogic::position_update_slot(MPR_TYPE view, double x, double y)
{
	switch (view)
	{
	case lwMPRBase::AXIAL:
		this->SetXPos(x);
		this->SetYPos(y);
		break;
	case lwMPRBase::CORONAL:
		this->SetXPos(x);
		this->SetZPos(y);
		break;
	case lwMPRBase::SAGITTAL:
		this->SetYPos(x);
		this->SetZPos(y);
		break;
	}
}

void lwMPRLogic::vector_update_slot(MPR_TYPE view, vector<double>& v1, vector<double>& v2)
{
	switch (view)
	{
	case lwMPRBase::AXIAL:
		this->SetXAxis(v1);
		this->SetYAxis(v2);
		break;
	case lwMPRBase::CORONAL:
		this->SetXAxis(v1);
		this->SetZAxis(v2);
		break;
	case lwMPRBase::SAGITTAL:
		this->SetYAxis(v1);
		this->SetZAxis(v2);
		break;
	}
}

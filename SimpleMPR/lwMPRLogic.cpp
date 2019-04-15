#include "lwMPRLogic.h"
#include "lwUtils.h"

lwMPRLogic::lwMPRLogic()
{
	//next = nullptr;
}

lwMPRLogic::~lwMPRLogic()
{
	//next = nullptr;
}

//void lwMPRLogic::SyncViewer(lwMPRLogic * viewer)
//{
//	next = viewer;
//}
//
//void lwMPRLogic::UpdateTheta(double t)
//{
//	//switch (this->GetView())
//	//{
//	//case lwMPRBase::AXIAL:
//	//	// z轴变换
//	//	auto x = this->GetXAxis();
//	//	x[0] *= cos(this->theta);
//	//	x[1] *= cos(this->theta);
//	//	this->SetXAxis();
//	//	this->SetYAxis();
//	//	break;
//	//case lwMPRBase::CORONAL:
//	//	// y轴变换
//	//	break;
//	//case lwMPRBase::SAGITTAL:
//	//	// x轴变换
//	//	break;
//	//}
//}
//
//void lwMPRLogic::UpdateSlice(double nslice)
//{
//	switch (this->GetView())
//	{
//	case lwMPRBase::AXIAL:
//		this->SetZPos(nslice);
//		break;
//	case lwMPRBase::CORONAL:
//		this->SetYPos(nslice);
//		break;
//	case lwMPRBase::SAGITTAL:
//		this->SetXPos(nslice);
//		break;
//	}
//	if (next)
//	{
//		if (!slice_connection.connected())
//		{
//			slice_connection = slice_signal.connect(
//				boost::bind(&lwMPRLogic::slice_update_slot, next, _1, _2));
//		}
//		slice_signal(this->GetView(), nslice);
//	}
//}
//
//void lwMPRLogic::UpdatePosition(double x, double y)
//{
//	switch (this->GetView())
//	{
//	case lwMPRBase::AXIAL:
//		this->SetXPos(x);
//		this->SetYPos(y);
//		break;
//	case lwMPRBase::CORONAL:
//		this->SetXPos(x);
//		this->SetZPos(y);
//		break;
//	case lwMPRBase::SAGITTAL:
//		this->SetYPos(x);
//		this->SetZPos(y);
//		break;
//	}
//	if (next)
//	{
//		if (!position_connection.connected())
//		{
//			position_connection = position_signal.connect(
//				boost::bind(&lwMPRLogic::position_update_slot, next, _1, _2, _3));
//		}
//		position_signal(this->GetView(), x, y);
//	}
//}
//
////void lwMPRLogic::UpdateHoriVector(vector<double>& vx)
////{
////	// xyz坐标系如图：
////	//		  y+|
////	//			|
////	//			|
////	//			|__________ x+
////	//		   /
////	//		  /
////	//	   z+/
////	// 1.AXIAL
////	//   - 视图对应XY平面
////	//   - x轴方向确定，则y轴方向由Z^X决定
////	//   - y轴方向确定，则x轴方向由Y^Z决定
////	// 2.CORONAL  
////	//   - 视图对应XZ平面
////	//   - x轴方向确定，则z轴方向由X^Y决定
////	//   - z轴方向确定，则x轴方向由Y^Z决定
////	// 3.SAGITTAL 
////	//	 - 视图对应YZ平面
////	//   - y轴方向确定，则z轴方向由X^Y决定
////	//   - z轴方向确定，则y轴方向由Z^X决定
////	lwUtils::Normalize(vx);
////	vector<double> vy;
////	switch (this->GetView())
////	{
////	case lwMPRBase::AXIAL:
////		vy = lwUtils::CrossProduct(this->GetZAxis(), vx);
////		break;
////	case lwMPRBase::CORONAL:
////		vy = lwUtils::CrossProduct(vx, this->GetYAxis());
////		break;
////	case lwMPRBase::SAGITTAL:
////		vy = lwUtils::CrossProduct(this->GetXAxis(), vx);
////		break;
////	}
////	this->SetHoriVector(vx);
////	this->SetVertVector(vy);
////
////	if (next)
////	{
////		if (!vector_connection.connected())
////		{
////			vector_connection = vector_signal.connect(
////				boost::bind(&lwMPRLogic::vector_update_slot, next, _1, _2, _3));
////		}
////		vector_signal(this->GetView(), vx, vy);
////	}
////}
////
////void lwMPRLogic::UpdateVertVector(vector<double>& vy)
////{
////	lwUtils::Normalize(vy);
////	vector<double> vx;
////	switch (this->GetView())
////	{
////	case lwMPRBase::AXIAL:
////		vx = lwUtils::CrossProduct(vy, this->GetZAxis());
////		break;
////	case lwMPRBase::CORONAL:
////		vx = lwUtils::CrossProduct(this->GetYAxis(), vy);
////		break;
////	case lwMPRBase::SAGITTAL:
////		vx = lwUtils::CrossProduct(vy, this->GetXAxis());
////		break;
////	}
////
////	this->SetHoriVector(vx);
////	this->SetVertVector(vy);
////
////	if (next)
////	{
////		if (!vector_connection.connected())
////		{
////			vector_connection = vector_signal.connect(
////				boost::bind(&lwMPRLogic::vector_update_slot, next, _1, _2, _3));
////		}
////		vector_signal(this->GetView(), vx, vy);
////	}
////}
//
//void lwMPRLogic::slice_update_slot(MPR_TYPE view, double nslice)
//{
//	if (this->GetView() == view)
//		return;
//
//	switch (view)
//	{
//	case lwMPRBase::AXIAL:
//		this->SetZPos(nslice);
//		break;
//	case lwMPRBase::CORONAL:
//		this->SetYPos(nslice);
//		break;
//	case lwMPRBase::SAGITTAL:
//		this->SetXPos(nslice);
//		break;
//	}
//	if (next)
//	{
//		if (!slice_connection.connected())
//		{
//			slice_connection = slice_signal.connect(
//				boost::bind(&lwMPRLogic::slice_update_slot, next, _1, _2));
//		}
//		slice_signal(view, nslice);
//	}
//}
//
//void lwMPRLogic::position_update_slot(MPR_TYPE view, double x, double y)
//{
//	if (this->GetView() == view)
//		return;
//
//	switch (view)
//	{
//	case lwMPRBase::AXIAL:
//		this->SetXPos(x);
//		this->SetYPos(y);
//		break;
//	case lwMPRBase::CORONAL:
//		this->SetXPos(x);
//		this->SetZPos(y);
//		break;
//	case lwMPRBase::SAGITTAL:
//		this->SetYPos(x);
//		this->SetZPos(y);
//		break;
//	}
//	if (next)
//	{
//		if (!position_connection.connected())
//		{
//			position_connection = position_signal.connect(
//				boost::bind(&lwMPRLogic::position_update_slot, next, _1, _2, _3));
//		}
//		position_signal(view, x, y);
//	}
//}
//
////void lwMPRLogic::vector_update_slot(MPR_TYPE view, vector<double>& vx, vector<double>& vy)
////{
////	if (this->GetView() == view)
////		return;
////
////	switch (view)
////	{
////		//	X^Y => Z
////		//	Z^X => Y
////		//	Y^Z => X
////	case lwMPRBase::AXIAL:
////	{
////		if (this->GetView() == lwMPRBase::CORONAL)
////		{
////			this->SetYAxis(vy);
////			auto v = lwUtils::CrossProduct(vy, this->GetZAxis());
////			this->SetXAxis(v);
////
////			this->SetHoriVector(this->GetXAxis());
////			this->SetVertVector(this->GetZAxis());
////		}
////		else if (this->GetView() == lwMPRBase::SAGITTAL)
////		{
////			this->SetXAxis(vx);
////			auto v = lwUtils::CrossProduct(this->GetZAxis(), vx);
////			this->SetYAxis(v);
////
////			this->SetHoriVector(this->GetYAxis());
////			this->SetVertVector(this->GetZAxis());
////		}
////		break;
////	}
////	case lwMPRBase::CORONAL:
////	{
////		if (this->GetView() == lwMPRBase::AXIAL)
////		{
////			this->SetZAxis(vy);
////			auto v = lwUtils::CrossProduct(this->GetYAxis(), vy);
////			this->SetXAxis(v);
////
////			this->SetHoriVector(this->GetXAxis());
////			this->SetVertVector(this->GetYAxis());
////		}
////		else if (this->GetView() == lwMPRBase::SAGITTAL)
////		{
////			this->SetXAxis(vx);
////			auto v = lwUtils::CrossProduct(vx, this->GetYAxis());
////			this->SetZAxis(v);
////
////			this->SetHoriVector(this->GetYAxis());
////			this->SetVertVector(this->GetZAxis());
////		}
////		break;
////	}
////	case lwMPRBase::SAGITTAL:
////	{
////		if (this->GetView() == lwMPRBase::CORONAL)
////		{
////			this->SetYAxis(vx);
////			auto v = lwUtils::CrossProduct(this->GetXAxis(), vx);
////			this->SetZAxis(v);
////
////			this->SetHoriVector(this->GetXAxis());
////			this->SetVertVector(this->GetZAxis());
////		}
////		else if (this->GetView() == lwMPRBase::AXIAL)
////		{
////			this->SetZAxis(vy);
////			auto v = lwUtils::CrossProduct(vy, this->GetXAxis());
////			this->SetYAxis(v);
////
////			this->SetHoriVector(this->GetXAxis());
////			this->SetVertVector(this->GetYAxis());
////		}
////		break;
////	}
////	}
////
////	if (next)
////	{
////		if (!vector_connection.connected())
////		{
////			vector_connection = vector_signal.connect(
////				boost::bind(&lwMPRLogic::vector_update_slot, next, _1, _2, _3));
////		}
////		vector_signal(view, vx, vy);
////	}
////}

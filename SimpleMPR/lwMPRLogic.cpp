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

void lwMPRLogic::UpdateTheta(double theta)
{
	//switch (this->GetView())
	//{
	//case lwMPRBase::AXIAL:
	//	this->SetGamma(theta);
	//	break;
	//case lwMPRBase::CORONAL:
	//	this->SetBeta(theta);
	//	break;
	//case lwMPRBase::SAGITTAL:
	//	this->SetAlpha(theta);
	//	break;
	//}
	if (next)
	{
		if (!theta_connection.connected())
		{
			theta_connection = theta_signal.connect(
				boost::bind(&lwMPRLogic::theta_update_slot, next, _1, _2));
		}
		theta_signal(this->GetView(), theta);
	}
}

void lwMPRLogic::theta_update_slot(MPR_TYPE view, double theta)
{
	if (this->GetView() != view)
	{
		switch (view)
		{
		case lwMPRBase::AXIAL:
			this->SetGamma(theta);
			break;
		case lwMPRBase::CORONAL:
			this->SetBeta(theta);
			break;
		case lwMPRBase::SAGITTAL:
			this->SetAlpha(theta);
			break;
		}
		if (next)
		{
			if (!theta_connection.connected())
			{
				theta_connection = theta_signal.connect(
					boost::bind(&lwMPRLogic::theta_update_slot, next, _1, _2));
			}
			theta_signal(view, theta);
			this->Render();
		}
	}
	else
		this->Render(theta);
}


void lwMPRLogic::UpdateSlice(double nslice)
{
	cout << this->GetView() << " : " << nslice << endl;
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
void lwMPRLogic::slice_update_slot(MPR_TYPE view, double nslice)
{
	if (this->GetView() != view)
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
		if (next)
		{
			if (!slice_connection.connected())
			{
				slice_connection = slice_signal.connect(
					boost::bind(&lwMPRLogic::slice_update_slot, next, _1, _2));
			}
			slice_signal(view, nslice);
		}
	}
	else
		this->Render();
}

void lwMPRLogic::position_update_slot(MPR_TYPE view, double x, double y)
{
	if (this->GetView() != view)
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
		if (next)
		{
			if (!position_connection.connected())
			{
				position_connection = position_signal.connect(
					boost::bind(&lwMPRLogic::position_update_slot, next, _1, _2, _3));
			}
			position_signal(view, x, y);

		}
	}
	else
		this->Render();
}


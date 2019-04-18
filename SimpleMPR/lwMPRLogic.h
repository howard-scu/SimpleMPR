#ifndef _LW_MPR_LOGIC_H
#define _LW_MPR_LOGIC_H

#include "lwMPRBase.h"
#include <boost\signals2.hpp>
#include <boost\bind.hpp>

class lwMPRLogic : public lwMPRBase
{
public:
	lwMPRLogic();
	~lwMPRLogic();

	double  GetNSlice()
	{
		switch (this->GetView())
		{
		case lwMPRLogic::AXIAL:
			return view_mat->GetElement(2, 3);
			break;
		case lwMPRLogic::CORONAL:
			return view_mat->GetElement(1, 3);
			break;
		case lwMPRLogic::SAGITTAL:
			return view_mat->GetElement(0, 3);
			break;
		}
	}
	void	UpdateSlice(double nslice);
	void	UpdatePosition(double x, double y);
	void	SyncViewer(lwMPRLogic* viewer);
	void	UpdateTheta(double theta);
	virtual void Render() = 0;
private:
	lwMPRLogic*		next;
	boost::signals2::signal<void(MPR_TYPE, double)>		slice_signal;
	boost::signals2::connection							slice_connection;
	void slice_update_slot(MPR_TYPE view, double nslice);

	boost::signals2::signal<void(MPR_TYPE, double, double)>		position_signal;
	boost::signals2::connection									position_connection;
	void position_update_slot(MPR_TYPE view, double x, double y);
	boost::signals2::signal<void(MPR_TYPE, double)>		theta_signal;
	boost::signals2::connection							theta_connection;
	void theta_update_slot(MPR_TYPE view, double theta);
};

#endif // !_LW_MPR_LOGIC_H

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

	void UpdateSlice(double nslice);
	void UpdatePosition(double x, double y);
	void UpdateHoriVector(vector<double>& v);
	void UpdateVertVector(vector<double>& v);
	void SyncViewer(lwMPRLogic* viewer);


private:
	lwMPRLogic* next;

	boost::signals2::signal<void(MPR_TYPE, double)>		slice_signal;
	boost::signals2::connection							slice_connection;
	void slice_update_slot(MPR_TYPE view, double nslice);

	boost::signals2::signal<void(MPR_TYPE, double, double)>		position_signal;
	boost::signals2::connection									position_connection;
	void position_update_slot(MPR_TYPE view, double x, double y);

	boost::signals2::signal<void(MPR_TYPE, vector<double>&, vector<double>&)>		vector_signal;
	boost::signals2::connection														vector_connection;
	void vector_update_slot(MPR_TYPE view, vector<double>& v1, vector<double>& v2);
};

#endif // !_LW_MPR_LOGIC_H

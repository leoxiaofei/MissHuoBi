#include "req\reqtimeline.h"
#include "common\timelinedata.h"
#include "tools\mspool.hpp"

#include <QJsonObject>
#include <QDateTime>

namespace HBAPI
{
	typedef MsPool<class Tag, TimeLineData> MPTLD;

	ReqTimeLine::ReqTimeLine()
	{

	}

	ReqTimeLine::~ReqTimeLine()
	{

	}

	int ReqTimeLine::SendRequest(SymbolIdType eSymbolId, const QDateTime& dtFrom, const QDateTime& dtTo)
	{
		QJsonObject json;
		json.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);

		if (dtFrom.isValid())
		{
			json.insert(szAttributeName[AN_FROM], (qint64)dtFrom.toTime_t());
		}

		if (dtTo.isValid())
		{
			json.insert(szAttributeName[AN_TO], (qint64)dtTo.toTime_t());
		}

		return SendJson(json);
	}

	bool ReqTimeLine::ReceiveJson(const QJsonObject& json)
	{
		QSharedPointer<TimeLineData> ptTimeLineData(MPTLD::New(), &MPTLD::Free);

		ParseTimeLineCylinder(json, *ptTimeLineData);

		emit signal_Receive(ptTimeLineData);

		return true;
	}

}
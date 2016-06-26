#include "req/reqkline.h"
#include "tools/mspool.hpp"
#include "common/klinedata.h"

#include <QJsonObject>
#include <QDebug>
#include <QDateTime>

namespace HBAPI
{
	typedef MsPool<class Tag, KLineData> MPKLD;

	ReqKLine::ReqKLine()
	{

	}

	ReqKLine::~ReqKLine()
	{

	}

	int ReqKLine::SendRequest(SymbolIdType eSymbolId, PeriodType ePeriodType, 
		const QDateTime& dtFrom, const QDateTime& dtTo)
	{
		QJsonObject json;
		json.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
		json.insert(szAttributeName[AN_PERIOD], szPeriodType[ePeriodType]);

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

	bool ReqKLine::ReceiveJson(const QJsonObject& json)
	{
		QSharedPointer<KLineData> ptKLineData(MPKLD::New(), &MPKLD::Free);

		ParseKLineData(json, *ptKLineData);

		emit signal_Receive(ptKLineData);

		return true;
	}


}

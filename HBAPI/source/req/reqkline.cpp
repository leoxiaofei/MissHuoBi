#include "req/reqkline.h"
#include "tools/mspool.hpp"
#include "common/klinedata.h"

#include <QJsonObject>
#include <QDebug>


namespace HBAPI
{
	typedef MsPool<class Tag, KLineData> MPKLD;

	ReqKLine::ReqKLine()
	{

	}

	ReqKLine::~ReqKLine()
	{

	}

	int ReqKLine::SendRequest(SymbolIdType eSymbolId, PeriodType ePeriodType)
	{
		QJsonObject json;
		json.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
		json.insert(szAttributeName[AN_PERIOD], szPeriodType[ePeriodType]);
		return SendJson(json);
	}

	bool ReqKLine::ReceiveJson(const QJsonObject& json)
	{
		qDebug() << json;

		QSharedPointer<KLineData> ptKLineData(MPKLD::New(), &MPKLD::Free);

		ParseKLineData(json, *ptKLineData);

		emit signal_Receive(ptKLineData);

		return true;
	}


}

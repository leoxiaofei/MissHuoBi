#include "msg/msglastkline.h"
#include "tools/mspool.hpp"
#include "common/misshbfunc.h"
#include "common/misshbdef.h"
#include "common/klinedata.h"

#include <QJsonObject>
#include <QSharedPointer>

namespace HBAPI
{
typedef MsPool<class Tag, LastKLineData> MPKLD;

Subscriber MsgLastKLine::GetSubscriber(SymbolIdType eSymbolId, 
	PushType ePushType, const QVector<PeriodType>& vecPeriodType)
{
	Subscriber sRet(MsgType());

	for (int ix = 0; ix != vecPeriodType.size(); ++ix)
	{
		QJsonObject js;

		js.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
		js.insert(szAttributeName[AN_PUSHTYPE], szPushType[ePushType]);
		js.insert(szAttributeName[AN_PERIOD], szPeriodType[vecPeriodType[ix]]);

		sRet.AddJsonObject(js);
	}

	return sRet;
}

bool MsgLastKLine::ReceiveJson(const QJsonObject& joPayload)
{
	QSharedPointer<LastKLineData> ptLastKLineData(MPKLD::New(), &MPKLD::Free);

	ParseLastKLineData(joPayload, *ptLastKLineData);

	emit signal_Receive(ptLastKLineData);

	return true;
}

}

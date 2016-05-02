#include "msg/msglastkline.h"
#include "tools/mspool.hpp"
#include "common/misshbfunc.h"
#include "common/misshbdef.h"

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

	ptLastKLineData->eSymbolId = GetSymbolIdType(joPayload[szAttributeName[AN_SYMBOLID]].toString());
	ptLastKLineData->ePeriod = GetPeriodType(joPayload[szAttributeName[AN_PERIOD]].toString());
	ptLastKLineData->tTime = joPayload[szAttributeName[AN_TIME]].toDouble();
	ptLastKLineData->dPriceOpen = joPayload[szAttributeName[AN_PRICEOPEN]].toDouble();
	ptLastKLineData->dPriceHigh = joPayload[szAttributeName[AN_PRICEHIGH]].toDouble();
	ptLastKLineData->dPriceLow = joPayload[szAttributeName[AN_PRICELOW]].toDouble();
	ptLastKLineData->dPriceLast = joPayload[szAttributeName[AN_PRICELAST]].toDouble();
	ptLastKLineData->dAmount = joPayload[szAttributeName[AN_AMOUNT]].toDouble();
	ptLastKLineData->dVolume = joPayload[szAttributeName[AN_VOLUME]].toDouble();
	ptLastKLineData->nCount = joPayload[szAttributeName[AN_COUNT]].toInt();

	return false;
}

}

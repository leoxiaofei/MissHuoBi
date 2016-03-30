#include "msglastkline.h"

#include <QJsonObject>


namespace HBAPI
{

Subscriber MsgLastKLine::GetSubscriber(SymbolIdType eSymbolId, 
	PushType ePushType, const QVector<PeriodType>& vecPeriodType)
{
	Subscriber sRet(this);

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
	return false;
}

}

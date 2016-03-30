#include "msgmarketdepthdiff.h"

#include <QJsonObject>

namespace HBAPI
{

	Subscriber MsgMarketDepthDiff::GetSubscriber(SymbolIdType eSymbolId, 
		PushType ePushType, const QVector<PercentType>& vecPercentType)
	{
		Subscriber sRet(this);

		for (int ix = 0; ix != vecPercentType.size(); ++ix)
		{
			QJsonObject js;

			js.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
			js.insert(szAttributeName[AN_PUSHTYPE], szPushType[ePushType]);
			js.insert(szAttributeName[AN_PERCENT], szPercentType[vecPercentType[ix]]);

			sRet.AddJsonObject(js);
		}

		return sRet;
	}

	bool MsgMarketDepthDiff::ReceiveJson(const QJsonObject& joPayload)
	{
		return false;

	}

}

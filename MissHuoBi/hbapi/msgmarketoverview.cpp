#include "msgmarketoverview.h"

#include <QJsonObject>

namespace HBAPI
{

	Subscriber MsgMarketOverview::GetSubscriber(SymbolIdType eSymbolId, PushType ePushType)
	{
		QJsonObject js;
		js.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
		js.insert(szAttributeName[AN_PUSHTYPE], szPushType[ePushType]);

		return Subscriber(this, js);
	}

	bool MsgMarketOverview::ReceiveJson(const QJsonObject& joPayload)
	{
		return false;

	}

}

#include "msgmarketdepthtopdiff.h"

#include <QJsonObject>

namespace HBAPI
{

	Subscriber MsgMarketDepthTopDiff::GetSubscriber(SymbolIdType eSymbolId, PushType ePushType)
	{
		QJsonObject js;
		js.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
		js.insert(szAttributeName[AN_PUSHTYPE], szPushType[ePushType]);

		return Subscriber(this, js);
	}

	bool MsgMarketDepthTopDiff::ReceiveJson(const QJsonObject& joPayload)
	{
		return false;

	}

}
#include "msg/msgmarketstatic.h"

#include <QJsonObject>

namespace HBAPI
{
	Subscriber MsgMarketStatic::GetSubscriber(SymbolIdType eSymbolId, PushType ePushType)
	{
		QJsonObject js;
		js.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
		js.insert(szAttributeName[AN_PUSHTYPE], szPushType[ePushType]);

		return Subscriber(MsgType(), js);
	}

	bool MsgMarketStatic::ReceiveJson(const QJsonObject& joPayload)
	{

		return false;

	}

}

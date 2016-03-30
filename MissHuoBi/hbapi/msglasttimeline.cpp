#include "msglasttimeline.h"

#include <QJsonObject>

namespace HBAPI
{
	Subscriber MsgLastTimeLine::GetSubscriber(SymbolIdType eSymbolId, PushType ePushType)
	{
		QJsonObject js;
		js.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
		js.insert(szAttributeName[AN_PUSHTYPE], szPushType[ePushType]);

		return Subscriber(this, js);
	}

	bool MsgLastTimeLine::ReceiveJson(const QJsonObject& joPayload)
	{
		return false;
	}

}

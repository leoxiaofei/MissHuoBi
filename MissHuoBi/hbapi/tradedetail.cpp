#include "tradedetail.h"
#include <QJsonObject>


namespace HBAPI
{

Subscriber HBAPI::TradeDetail::GetSubscriber(const QString& symbolId, PushType ePushType)
{
	QJsonObject js;
	js.insert(szAttributeName[AN_SYMBOLID], symbolId);
	js.insert(szAttributeName[AN_PUSHTYPE], szPushType[ePushType]);

	return Subscriber(this, js);
}

}

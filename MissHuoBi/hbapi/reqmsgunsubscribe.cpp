#include "reqmsgunsubscribe.h"
#include <QJsonObject>
#include "subscribebase.h"


namespace HBAPI
{

int ReqMsgUnsubscribe::SendRequest(const QVector<Subscriber>& vecSubscriber)
{
	QJsonObject json;

	QJsonObject jsonSub;

	for (QVector<Subscriber>::const_iterator citor = vecSubscriber.constBegin();
		citor != vecSubscriber.constEnd(); ++citor)
	{
		citor->Apply(jsonSub);
	}

	json.insert(szAttributeName[AN_SYMBOLLIST], jsonSub);

	return SendJson(json);
}

bool ReqMsgUnsubscribe::ReceiveJson(const QJsonObject& json)
{
	return false;
}

}

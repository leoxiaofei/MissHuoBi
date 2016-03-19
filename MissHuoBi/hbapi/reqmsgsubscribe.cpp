#include "reqmsgsubscribe.h"
#include "subscribebase.h"

#include <QJsonObject>

namespace HBAPI
{

int ReqMsgSubscribe::SendRequest(const QVector<Subscriber>& vecSubscriber)
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

bool ReqMsgSubscribe::ReceiveJson(const QJsonObject& json)
{
	return true;
}

}

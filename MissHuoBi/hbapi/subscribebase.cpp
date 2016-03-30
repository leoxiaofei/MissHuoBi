#include "subscribebase.h"
#include <QJsonObject>


namespace HBAPI
{

Subscriber::Subscriber(SubscribeBase* pBase)
	: pSubscribeBase(pBase)
{

}

Subscriber::Subscriber(SubscribeBase* pBase, const QJsonObject& json)
	: pSubscribeBase(pBase)
{
	AddJsonObject(json);
}

Subscriber::~Subscriber()
{

}


void Subscriber::AddJsonObject(const QJsonObject& json)
{
	jsValue.append(json);
}

void Subscriber::Apply(QJsonObject& jParent) const
{
	jParent.insert(pSubscribeBase->GetMsgType(), jsValue);
}

};

#include "msg/subscribebase.h"
#include <QJsonObject>


namespace HBAPI
{

	Subscriber::Subscriber(const char* szMsgType)
		: szMsgType(szMsgType)
	{

	}

	Subscriber::Subscriber(const char* szMsgType, const QJsonObject& json)
		: szMsgType(szMsgType)
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
		jParent.insert(szMsgType, jsValue);
	}

};

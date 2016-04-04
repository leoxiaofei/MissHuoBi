#include "req/requestbase.h"
#include <QJsonObject>


namespace HBAPI
{

	void RequestBase::SetSendFunc(const SendFunc& funcSend)
	{
		m_funcSend = funcSend;
	}

	int RequestBase::SendJson(QJsonObject& json)
	{
		json.insert(szAttributeName[AN_MSGTYPE], QString(GetReqType()));

		return m_funcSend(json);
	}


}

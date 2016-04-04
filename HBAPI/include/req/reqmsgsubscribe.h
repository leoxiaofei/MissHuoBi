#ifndef __REQMSGSUBSCRIBE_H__
#define __REQMSGSUBSCRIBE_H__


#include "requestbase.h"
#include <QVector>

/*
�����ӿ�
������Ϣ����
*/

namespace HBAPI
{
	class Subscriber;

	class HBAPI_EXPORT ReqMsgSubscribe : public RequestBase
	{
		REQTYPE(reqMsgSubscribe);
	public:
		int SendRequest(const QVector<Subscriber>& vecSubscriber);

	protected:
		virtual bool ReceiveJson(const QJsonObject& json) override;

	};

}

#endif // __REQMSGSUBSCRIBE_H__

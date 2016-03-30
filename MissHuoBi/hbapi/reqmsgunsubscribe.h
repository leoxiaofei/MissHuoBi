#ifndef __REQMSGUNSUBSCRIBE_H__
#define __REQMSGUNSUBSCRIBE_H__



#include "requestbase.h"
#include <QVector>

/*
�����ӿ�
������Ϣȡ������
*/

namespace HBAPI
{
	class Subscriber;

	class ReqMsgUnsubscribe : public RequestBase
	{
		REQTYPE(reqMsgUnsubscribe);
	public:
		int SendRequest(const QVector<Subscriber>& vecSubscriber);

	protected:
		virtual bool ReceiveJson(const QJsonObject& json) override;

	};

}



#endif // __REQMSGUNSUBSCRIBE_H__

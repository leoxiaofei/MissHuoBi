#ifndef __MSGLASTTIMELINE_H__
#define __MSGLASTTIMELINE_H__

#include "subscribebase.h"

#include <QVector>

namespace HBAPI
{
	class MsgLastTimeLine : public SubscribeBase
	{
		MSGTYPE(lastTimeLine);
	public:
		Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	};

}

#endif // __MSGLASTTIMELINE_H__

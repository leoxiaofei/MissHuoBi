#ifndef __MSGMARKETSTATIC_H__
#define __MSGMARKETSTATIC_H__


#include "subscribebase.h"

namespace HBAPI
{
	class MsgMarketStatic : public SubscribeBase
	{
		MSGTYPE(marketStatic);
	public:
		Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	};

}


#endif // __MSGMARKETSTATIC_H__

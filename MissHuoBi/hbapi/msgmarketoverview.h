#ifndef __MSGMARKETOVERVIEW_H__
#define __MSGMARKETOVERVIEW_H__


#include "subscribebase.h"

namespace HBAPI
{
	class MsgMarketOverview : public SubscribeBase
	{
		MSGTYPE(marketOverview);
	public:
		Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	};

}


#endif // __MSGMARKETOVERVIEW_H__
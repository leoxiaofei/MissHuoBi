#ifndef __MSGMARKETDEPTHTOPDIFF_H__
#define __MSGMARKETDEPTHTOPDIFF_H__

#include "subscribebase.h"

namespace HBAPI
{
	class MsgMarketDepthTopDiff : public SubscribeBase
	{
		MSGTYPE(marketDepthTopDiff);
	public:
		Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	};

}

#endif // __MSGMARKETDEPTHTOPDIFF_H__

#ifndef __MSGMARKETDEPTHTOPDIFF_H__
#define __MSGMARKETDEPTHTOPDIFF_H__

#include "subscribebase.h"

#include "common/asksdata.h"
#include "common/bidsdata.h"

namespace HBAPI
{
	class MarketDepthTopDiffData;

	class HBAPI_EXPORT MsgMarketDepthTopDiff : public SubscribeBase
	{
		Q_OBJECT
		MSGTYPE(marketDepthTopDiff);
	public:
		static Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	signals:
		void signal_Receive(const QSharedPointer<MarketDepthTopDiffData>& ptMarketDepthTopDiffData);

	};

}

#endif // __MSGMARKETDEPTHTOPDIFF_H__

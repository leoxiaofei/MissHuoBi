#ifndef __MSGMARKETDEPTHTOPDIFF_H__
#define __MSGMARKETDEPTHTOPDIFF_H__

#include "subscribebase.h"

#include "common/asksdata.h"
#include "common/bidsdata.h"

namespace HBAPI
{
	class HBAPI_EXPORT MarketDepthTopDiffData
	{
	public:
		SymbolIdType				eSymbolId;
		quint64						uVersion;
		quint64						uVersionOld;
		QVector<AskInsertData>		vecAskInsertData;
		QVector<AskDeleteData>		vecAskDeleteData;
		QVector<AskUpdateData>		vecAskUpdateData;
		QVector<BidInsertData>		vecBidInsertData;
		QVector<BidDeleteData>		vecBidDeleteData;
		QVector<BidUpdateData>		vecBidUpdateData;
	};

	class HBAPI_EXPORT MsgMarketDepthTopDiff : public SubscribeBase
	{
		MSGTYPE(marketDepthTopDiff);
	public:
		static Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	};

}

#endif // __MSGMARKETDEPTHTOPDIFF_H__

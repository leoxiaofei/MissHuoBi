#ifndef __MSGMARKETDEPTHDIFF_H__
#define __MSGMARKETDEPTHDIFF_H__

#include "subscribebase.h"

#include "common/asksdata.h"
#include "common/bidsdata.h"

namespace HBAPI
{
	class HBAPI_EXPORT MarketDepthDiffData
	{
	public:
		SymbolIdType				eSymbolId;
		PercentType					ePercentType;
		quint64						uVersion;
		quint64						uVersionOld;
		QVector<AskInsertData>		vecAskInsertData;
		QVector<AskDeleteData>		vecAskDeleteData;
		QVector<AskUpdateData>		vecAskUpdateData;
		QVector<BidInsertData>		vecBidInsertData;
		QVector<BidDeleteData>		vecBidDeleteData;
		QVector<BidUpdateData>		vecBidUpdateData;
	};

	class HBAPI_EXPORT MsgMarketDepthDiff : public SubscribeBase
	{
		MSGTYPE(marketDepthDiff);
	public:
		static Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType,
			const QVector<PercentType>& vecPercentType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	};

}

#endif // __MSGMARKETDEPTHDIFF_H__
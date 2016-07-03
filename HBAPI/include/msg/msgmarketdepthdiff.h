#ifndef __MSGMARKETDEPTHDIFF_H__
#define __MSGMARKETDEPTHDIFF_H__

#include "subscribebase.h"

#include "common/asksdata.h"
#include "common/bidsdata.h"

namespace HBAPI
{
	class MarketDepthDiffData;

	class HBAPI_EXPORT MsgMarketDepthDiff : public SubscribeBase
	{
		Q_OBJECT
		MSGTYPE(marketDepthDiff);
	public:
		static Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType,
			const QVector<PercentType>& vecPercentType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	signals:
		void signal_Receive(const QSharedPointer<MarketDepthDiffData>& ptMarketDepthDiffData);
	};

}

#endif // __MSGMARKETDEPTHDIFF_H__
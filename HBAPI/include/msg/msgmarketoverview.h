#ifndef __MSGMARKETOVERVIEW_H__
#define __MSGMARKETOVERVIEW_H__


#include "subscribebase.h"

namespace HBAPI
{
	class HBAPI_EXPORT MarketOverviewData
	{
	public:
		SymbolIdType				eSymbolId;				   ///交易代码
		double						dPriceNew;				   ///当前价格
		double						dPriceOpen;				   ///开盘
		double						dPriceHigh;				   ///最高
		double						dPriceLow;				   ///最低
		double						dPriceAsk;				   ///卖一
		double						dPriceBid;				   ///买一
		double						dTotalVolume;			   ///今日累计成交量
		double						dTotalAmount;			   ///今日累计成交额
	};

	class HBAPI_EXPORT MsgMarketOverview : public SubscribeBase
	{
		Q_OBJECT
		MSGTYPE(marketOverview);
	public:
		MsgMarketOverview();
		~MsgMarketOverview();

		static Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	signals:
		void signal_Receive(const QSharedPointer<MarketOverviewData>& ptMarketOverviewData);

	};

}


#endif // __MSGMARKETOVERVIEW_H__
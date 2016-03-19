#ifndef __MSGMARKETDETAIL_H__
#define __MSGMARKETDETAIL_H__


#include "subscribebase.h"
#include <boost\rational.hpp>


namespace HBAPI
{
	class MarketDetailBill
	{
	public:
		SymbolIdType				eSymbolId;
		boost::rational<int>		rPriceNew;
		boost::rational<int>		rPriceOpen;
		boost::rational<int>		rPriceHigh;
		boost::rational<int>		rPriceLow;
		boost::rational<int>		rPriceLast;
		int32_t						nLevel;
		boost::rational<int>		rAmount;
		boost::rational<int>		rTotalAmount;
// 		Amp;
// 		Trades;
// 		Bids;
// 		Asks;
// 		CommissionRatio;
// 		Poor;
// 		UpdownVolume;
// 		UpdownRatio;
// 		PriceAverage;
// 		VolumeRatio;
// 		TurnVolume;
// 		TurnoverRate;
// 		OuterDisc;
// 		InnerDisc;
// 		TotalVolume;
	};

	class MsgMarketDetail : public SubscribeBase
	{
		MSGTYPE(marketDetail);
	public:
		Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	};

}


#endif // __MSGMARKETDETAIL_H__

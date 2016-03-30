#ifndef __MSGMARKETDETAIL_H__
#define __MSGMARKETDETAIL_H__


#include "subscribebase.h"
#include "bidsdata.h"
#include "asksdata.h"
#include "tradesdata.h"

#include <QSharedPointer>

namespace HBAPI
{
	class MarketDetailBill
	{
	public:
		SymbolIdType	eSymbolId;
		double			dPriceNew;					///最新成交价
		double			dPriceOpen;					///最近24小时开盘
		double			dPriceHigh;					///最近24小时最高
		double			dPriceLow;					///最近24小时最低
		double			dPriceLast;					///最近24小时收盘
		double			dPriceAverage;				///均价
		double			dAmount;					///成交量
		double			dTotalAmount;				///最近24小时成交量
		double			dTotalVolume;				///最近24小时成交额

		double			dUpdownVolume;				///涨跌量：最新价减去开盘价，原来的level字段
		double			dUpdownRatio;				///涨跌幅：涨跌比例：level比开盘价，原来的amp字段
		double			dTurnVolume;				///金额
		double			dTurnoverRate;				///换手
		double			dCommissionRatio;			///委比：(委买手数－委卖手数)/(委买手数＋委卖手数)*100%
		double			dPoor;						///委差：委买委卖的差值（即委差）
		double			dOuterDisc;					///外盘：外盘(即买盘):是指以卖出价成交的股票手数,就是先有卖出的价格,而后才有成交;而内盘(即卖盘):是指以买进价格成交的股票手数,就是先有买进的价格,而后才有成交;
		double			dInnerDisc;					///内盘
		double			dVolumeRatio;

		QVector<BidsData>		vecBidsData;		///买单
		QVector<AsksData>		vecAsksData;		///卖单
		QVector<TradesData>		vecTradesData;		///成交单

// 		double			dLevel;
// 		double			dAmp;

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

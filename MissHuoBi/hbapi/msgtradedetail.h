#ifndef __TRADEDETAIL_H__
#define __TRADEDETAIL_H__

#include "subscribebase.h"
#include "misshbdef.h"
#include <boost\rational.hpp>
#include <QVector>
#include "bidsdata.h"
#include "asksdata.h"

namespace HBAPI
{
	class TradeDetailData
	{
	public:
		int						nTradeId;			///交易id
		time_t					tTime;
		double					dPrice;				///价格
		double					dAmount;			///成交量
		DirectionType			eDirection;			///交易方向：买入和卖出

		QVector<BidsData>		vecTopBidsData;		///Top买单
		QVector<AsksData>		vecTopAsksData;		///Top卖单
	};

	class TradeDetailBill
	{
	public:
		SymbolIdType				eSymbolId;
		QVector<TradeDetailData*>	vecTradeDetailData;

	public:
		~TradeDetailBill();
		void Resize(int nSize);
		void Free();
	};

	class MsgTradeDetail : public SubscribeBase
	{
		MSGTYPE(tradeDetail);
	public:
		Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	};

}


#endif // __TRADEDETAIL_H__

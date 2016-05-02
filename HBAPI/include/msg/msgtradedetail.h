#ifndef __TRADEDETAIL_H__
#define __TRADEDETAIL_H__

#include "msg/subscribebase.h"
#include "common/misshbdef.h"
#include "common/bidsdata.h"
#include "common/asksdata.h"

#include <QSharedPointer>
#include <QVector>

namespace HBAPI
{
	class HBAPI_EXPORT TradeDetailData
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

	class HBAPI_EXPORT TradeDetailBill
	{
	public:
		SymbolIdType				eSymbolId;
		QVector<TradeDetailData*>	vecTradeDetailData;

	public:
		~TradeDetailBill();
		void Resize(int nSize);
		void Free();
	};

	class HBAPI_EXPORT MsgTradeDetail : public SubscribeBase
	{
		Q_OBJECT
		MSGTYPE(tradeDetail);
	public:
		static Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	signals:
		void signal_Receive(const QSharedPointer<TradeDetailBill>& ptTradeDetailBill);
	};

}


#endif // __TRADEDETAIL_H__

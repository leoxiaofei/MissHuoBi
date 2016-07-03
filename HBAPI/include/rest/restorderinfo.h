#ifndef __RESTORDERINFO_H__
#define __RESTORDERINFO_H__

#include "restrequestbase.h"

namespace HBAPI
{
	class HBAPI_EXPORT OrderInfo
	{
	public:
		int			nId;					 ///委托订单id
		OrderType	eType;					 ///委托订单类型
		double		dOrderPrice;			 ///委托价格
		double		dOrderAmount;			 ///委托数量(市价买单，代表买入金额)
		double		dProcessedPrice;		 ///成交平均价格
		double		dProcessedAmount;		 ///已经完成的数量(市价买单，代表成交金额)
		double		dVot;					 ///交易额
		double		dFee;					 ///手续费
		double		dTotal;					 ///总交易额（只有人民币交易市场才会返回）
		OrderStatus	eStatus;				 ///状态
	};

	///获取委托详情 
	class HBAPI_EXPORT RestOrderInfo : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(order_info);
	public:
		void SendRequest(CoinType eCoinType, unsigned int uOrderId, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json, int nCode) override;

	signals:
		void signal_Receive(const QSharedPointer<OrderInfo>& ptOrderInfo);
	};

}

#endif // __RESTORDERINFO_H__

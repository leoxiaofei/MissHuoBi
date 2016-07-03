#ifndef __RESTGETORDERS_H__
#define __RESTGETORDERS_H__

#include "restrequestbase.h"

#include <QDateTime>

namespace HBAPI
{
	class HBAPI_EXPORT OrdersData
	{
	public:
		int			nId;					///委托订单id
		OrderType	eType;					///委托订单类型
		double		dOrderPrice;			///委托价格
		double		dOrderAmount;			///委托数量(市价买单，代表买入金额)
		double		dProcessedAmount;		///已经完成的数量(市价买单，代表成交金额)
		QDateTime	dtOrderTime;			///委托时间
	};

	///获取所有正在进行的委托 
	class HBAPI_EXPORT RestGetOrders : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(get_orders);
	public:
		void SendRequest(CoinType eCoinType, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json, int nCode) override;

	signals:
		void signal_Receive(const QList<OrdersData>& listOrdersData);

	};


}
#endif // __RESTGETORDERS_H__

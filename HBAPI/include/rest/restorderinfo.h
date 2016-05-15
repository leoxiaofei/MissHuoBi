#ifndef __RESTORDERINFO_H__
#define __RESTORDERINFO_H__

#include "restrequestbase.h"

namespace HBAPI
{
	class OrderInfo
	{
	public:
// 		Id;
// 		Type;
// 		Order_price;
// 		Order_amount;
// 		Processed_price;
// 		Processed_amount;
// 		Vot;
// 		Fee;
// 		Total;
// 		Status;
	};

	///获取委托详情 
	class HBAPI_EXPORT RestOrderInfo : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(order_info);
	public:
		void SendRequest(CoinType eCoinType, unsigned int uOrderId, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json, int nCode) override;

	};

}

#endif // __RESTORDERINFO_H__

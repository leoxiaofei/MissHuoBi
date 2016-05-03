#ifndef __RESTGETORDERS_H__
#define __RESTGETORDERS_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///获取所有正在进行的委托 
	class HBAPI_EXPORT RestGetOrders : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(get_orders);
	public:
		void SendRequest(CoinType eCoinType, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json) override;

	};


}
#endif // __RESTGETORDERS_H__

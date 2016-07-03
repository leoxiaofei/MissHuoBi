#ifndef __RESTGETORDERIDBYTRADEID_H__
#define __RESTGETORDERIDBYTRADEID_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///¸ù¾Ýtrade_id²éÑ¯oder_id 
	class HBAPI_EXPORT RestGetOrderIdByTradeId : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(get_order_id_by_trade_id);
	public:
		void SendRequest(CoinType eCoinType, unsigned int uTradeId,
			MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json, int nCode) override;

	};


}
#endif // __RESTGETORDERIDBYTRADEID_H__

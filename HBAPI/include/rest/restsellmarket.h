#ifndef __RESTSELLMARKET_H__
#define __RESTSELLMARKET_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///卖出(市价单) 
	class HBAPI_EXPORT RestSellMarket : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(sell_market);
	public:
		void SendRequest(CoinType eCoinType, const double& dAmount,
			MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json) override;

	};


}

#endif // __RESTSELLMARKET_H__

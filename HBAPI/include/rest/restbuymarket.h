#ifndef __RESTBUYMARKET_H__
#define __RESTBUYMARKET_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///买入(市价单) 
	class HBAPI_EXPORT RestBuyMarket : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(buy_market);
	public:
		void SendRequest(CoinType eCoinType, const double& dAmount, 
			MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json, int nCode) override;

	};


}

#endif // __RESTBUYMARKET_H__

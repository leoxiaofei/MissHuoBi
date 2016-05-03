#ifndef __RESTBUY_H__
#define __RESTBUY_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///¬Ú»Î
	class HBAPI_EXPORT RestBuy : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(buy);
	public:
		void SendRequest(CoinType eCoinType, const double& dPrice, 
			const double& dAmount, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json) override;

	};


}

#endif // __RESTBUY_H__

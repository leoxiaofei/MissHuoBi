#ifndef __RESTSELL_H__
#define __RESTSELL_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///Âô³ö 
	class HBAPI_EXPORT RestSell : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(sell);
	public:
		void SendRequest(CoinType eCoinType, const double& dPrice,
			const double& dAmount, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json) override;

	};


}

#endif // __RESTSELL_H__

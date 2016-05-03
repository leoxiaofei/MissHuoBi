#ifndef __RESTWITHDRAWCOIN_H__
#define __RESTWITHDRAWCOIN_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///���BTC/LTC 
	class HBAPI_EXPORT RestWithdrawCoin : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(withdraw_coin);
	public:
		void SendRequest(CoinType eCoinType, const QString& strWithdrawAddress,
			const double& dWithdrawAmount, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json) override;

	};


}

#endif // __RESTWITHDRAWCOIN_H__

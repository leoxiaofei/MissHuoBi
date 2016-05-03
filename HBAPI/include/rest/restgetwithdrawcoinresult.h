#ifndef __RESTGETWITHDRAWCOINRESULT_H__
#define __RESTGETWITHDRAWCOINRESULT_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///≤È—ØÃ·±“BTC/LTC 
	class HBAPI_EXPORT RestGetWithdrawCoinResult : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(get_withdraw_coin_result);
	public:
		void SendRequest(unsigned int uWithdrawCoinId, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json) override;

	};


}
#endif // __RESTGETWITHDRAWCOINRESULT_H__

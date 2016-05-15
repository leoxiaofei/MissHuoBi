#ifndef __RESTCANCELWITHDRAWCOIN_H__
#define __RESTCANCELWITHDRAWCOIN_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///»°œ˚Ã·±“BTC/LTC 
	class HBAPI_EXPORT RestCancelWithdrawCoin : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(cancel_withdraw_coin);
	public:
		void SendRequest(unsigned int uWithdrawCoinId, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json, int nCode) override;

	};


}
#endif // __RESTCANCELWITHDRAWCOIN_H__

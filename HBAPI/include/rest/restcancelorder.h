#ifndef __RESTCANCELORDER_H__
#define __RESTCANCELORDER_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///取消委托单 
	class HBAPI_EXPORT RestCancelOrder : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(cancel_order);
	public:
		void SendRequest(CoinType eCoinType, unsigned int uOrderId, 
			MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json, int nCode) override;

	signals:
		void signal_Receive(bool bResult);
	};


}

#endif // __RESTCANCELORDER_H__

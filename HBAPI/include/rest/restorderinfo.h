#ifndef __RESTORDERINFO_H__
#define __RESTORDERINFO_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///��ȡί������ 
	class HBAPI_EXPORT RestOrderInfo : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(order_info);
	public:
		void SendRequest(CoinType eCoinType, unsigned int uOrderId, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json) override;

	};

}

#endif // __RESTORDERINFO_H__

#ifndef __RESTCANCELORDER_H__
#define __RESTCANCELORDER_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///ȡ��ί�е� 
	class HBAPI_EXPORT RestCancelOrder : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(cancel_order);
	public:
		void SendRequest(CoinType eCoinType, unsigned int uOrderId, 
			MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json, int nCode) override;

	};


}

#endif // __RESTCANCELORDER_H__

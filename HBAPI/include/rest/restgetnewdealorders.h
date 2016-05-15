#ifndef __RESTGETNEWDEALORDERS_H__
#define __RESTGETNEWDEALORDERS_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///��ѯ��������10���ɽ����� 
	class HBAPI_EXPORT RestGetNewDealOrders : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(get_new_deal_orders);
	public:
		void SendRequest(CoinType eCoinType, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json, int nCode) override;

	};


}
#endif // __RESTGETNEWDEALORDERS_H__

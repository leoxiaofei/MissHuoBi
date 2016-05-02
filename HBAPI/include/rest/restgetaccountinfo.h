#ifndef __RESTGETACCOUNTINFO_H__
#define __RESTGETACCOUNTINFO_H__

#include "restrequestbase.h"

namespace HBAPI
{

	class HBAPI_EXPORT RestGetAccountInfo : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(get_account_info);
	public:
		void SendRequest(MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonObject& json) override;

	};



}



#endif // __RESTGETACCOUNTINFO_H__

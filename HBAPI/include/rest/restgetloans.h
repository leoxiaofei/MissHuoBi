#ifndef __RESTGETLOANS_H__
#define __RESTGETLOANS_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///≤È—Ø∏‹∏À¡–±Ì 
	class HBAPI_EXPORT RestGetLoans : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(get_loans);
	public:
		void SendRequest(MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json) override;

	};


}
#endif // __RESTGETLOANS_H__

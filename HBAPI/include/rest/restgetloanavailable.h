#ifndef __RESTGETLOANAVAILABLE_H__
#define __RESTGETLOANAVAILABLE_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///≤È—Øø……Í«Î∏‹∏À∂Ó∂» 
	class HBAPI_EXPORT RestGetLoanAvailable : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(get_loan_available);
	public:
		void SendRequest(MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json) override;

	};


}
#endif // __RESTGETLOANAVAILABLE_H__

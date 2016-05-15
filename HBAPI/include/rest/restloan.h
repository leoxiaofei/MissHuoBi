#ifndef __RESTLOAN_H__
#define __RESTLOAN_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///…Í«Î∏‹∏À 
	class HBAPI_EXPORT RestLoan : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(loan);
	public:
		void SendRequest(LoanType eLoanType, const double& dAmount, 
			MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json, int nCode) override;

	};


}
#endif // __RESTLOAN_H__

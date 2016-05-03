#ifndef __RESTREPAYMENT_H__
#define __RESTREPAYMENT_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///�黹�ܸ� 
	class HBAPI_EXPORT RestRepayment : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(repayment);
	public:
		void SendRequest(unsigned int uLoanId, const double& dAmount,
			int nRepayAll = 0, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json) override;

	};


}

#endif // __RESTREPAYMENT_H__

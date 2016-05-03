#ifndef __RESTTRANSFER_H__
#define __RESTTRANSFER_H__

#include "restrequestbase.h"

namespace HBAPI
{
	///ÕË»§ÄÚ×ªÕË
	class HBAPI_EXPORT RestTransfer : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(transfer);
	public:
		void SendRequest(CoinType eCoinType,
			AccountType eAccountFrom, AccountType eAccountTo,
			const double& dAmount, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json) override;

	};


}

#endif // __RESTTRANSFER_H__

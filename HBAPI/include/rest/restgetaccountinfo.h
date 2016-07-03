#ifndef __RESTGETACCOUNTINFO_H__
#define __RESTGETACCOUNTINFO_H__

#include "restrequestbase.h"

namespace HBAPI
{
	class HBAPI_EXPORT AccountInfoData
	{
	public:
		double dAvailableBtcDisplay;
		double dLoanCnyDisplay;
		double dFrozenCnyDisplay;
		double dAvailableLtcDisplay;
		double dLoanBtcDisplay;
		double dFrozenBtcDisplay;
		double dNetAsset;
		double dLoanLtcDisplay;
		double dFrozenLtcDisplay;
		double dAvailableCnyDisplay;
		double dTotal;
	};

	///获取个人资产信息 
	class HBAPI_EXPORT RestGetAccountInfo : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(get_account_info);
	public:
		void SendRequest(MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json, int nCode) override;

	signals:
		void signal_Receive(const QSharedPointer<AccountInfoData>& ptAccountInfoData);

	};


}



#endif // __RESTGETACCOUNTINFO_H__

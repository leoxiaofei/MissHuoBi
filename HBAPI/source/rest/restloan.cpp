#include "rest\restloan.h"
#include "common\mapkv.h"

#include <QDebug>

namespace HBAPI
{

	void RestLoan::SendRequest(LoanType eLoanType, const double& dAmount,
		MarketType eMarketType)
	{
		MapKV mapParams;
		mapParams.insert(szRestKName[RK_LOAN_TYPE], eLoanType);
		mapParams.insert(szRestKName[RK_AMOUNT], dAmount);

		if (eMarketType != MT_CNY)
		{
			MapKV mapExtra;
			mapExtra.insert(szRestKName[RK_MARKET], szMarketType[eMarketType]);
			SendRest(mapParams, mapExtra);
		}
		else
		{
			SendRest(mapParams);
		}
	}

	bool RestLoan::ReceiveJson(const QJsonDocument& json, int nCode)
	{
		qDebug() << json;

		return false;
	}

}


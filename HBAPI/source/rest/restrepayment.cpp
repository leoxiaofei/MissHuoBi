#include "rest\restrepayment.h"
#include "common\mapkv.h"

#include <QDebug>

namespace HBAPI
{

	void RestRepayment::SendRequest(unsigned int uLoanId, 
		const double& dAmount, int nRepayAll,
		MarketType eMarketType)
	{
		MapKV mapParams;
		mapParams.insert(szRestKName[RK_AMOUNT], dAmount);

		if (eMarketType != MT_CNY && nRepayAll != 0)
		{
			MapKV mapExtra;
			mapExtra.insert(szRestKName[RK_MARKET], szMarketType[eMarketType]);
			mapExtra.insert(szRestKName[RK_REPAY_ALL], nRepayAll);
			SendRest(mapParams, mapExtra);
		}
		else
		{
			SendRest(mapParams);
		}
	}

	bool RestRepayment::ReceiveJson(const QJsonDocument& json, int nCode)
	{
		qDebug() << json;

		return false;
	}

}


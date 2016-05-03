#include "rest\resttransfer.h"
#include "common\mapkv.h"

#include <QDebug>

namespace HBAPI
{

	void RestTransfer::SendRequest(CoinType eCoinType,
		AccountType eAccountFrom, AccountType eAccountTo,
		const double& dAmount, MarketType eMarketType)
	{
		MapKV mapParams;
		mapParams.insert(szRestKName[RK_COIN_TYPE], eCoinType);
		mapParams.insert(szRestKName[RK_ACCOUNT_FROM], eAccountFrom);
		mapParams.insert(szRestKName[RK_ACCOUNT_TO], eAccountTo);
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

	bool RestTransfer::ReceiveJson(const QJsonDocument& json)
	{
		qDebug() << json;

		return false;
	}

}


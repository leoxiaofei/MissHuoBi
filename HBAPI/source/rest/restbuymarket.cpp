#include "rest\restbuymarket.h"
#include "common\mapkv.h"

#include <QDebug>

namespace HBAPI
{

	void RestBuyMarket::SendRequest(CoinType eCoinType, 
		const double& dAmount, MarketType eMarketType)
	{
		MapKV mapParams;
		mapParams.insert(szRestKName[RK_COIN_TYPE], eCoinType);
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

	bool RestBuyMarket::ReceiveJson(const QJsonDocument& json)
	{
		qDebug() << json;

		return false;
	}

}


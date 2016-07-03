#include "rest\restsellmarket.h"
#include "common\mapkv.h"

#include <QDebug>

namespace HBAPI
{

	void RestSellMarket::SendRequest(CoinType eCoinType, 
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

	bool RestSellMarket::ReceiveJson(const QJsonDocument& json, int nCode)
	{
		qDebug() << json;

		return false;
	}

}


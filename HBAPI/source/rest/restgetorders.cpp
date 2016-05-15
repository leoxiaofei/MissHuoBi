#include "rest\restgetorders.h"
#include "common\mapkv.h"

#include <QDebug>

namespace HBAPI
{

	void RestGetOrders::SendRequest(CoinType eCoinType, MarketType eMarketType)
	{
		MapKV mapParams;

		mapParams.insert(szRestKName[RK_COIN_TYPE], eCoinType);	

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

	bool RestGetOrders::ReceiveJson(const QJsonDocument& json, int nCode)
	{
		qDebug() << json;

		return false;
	}

}


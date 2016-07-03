#include "rest\restgetorderidbytradeid.h"
#include "common\mapkv.h"

#include <QDebug>

namespace HBAPI
{

	void RestGetOrderIdByTradeId::SendRequest(CoinType eCoinType, 
		unsigned int uTradeId, MarketType eMarketType)
	{
		MapKV mapParams;
		mapParams.insert(szRestKName[RK_COIN_TYPE], eCoinType);
		mapParams.insert(szRestKName[RK_TRADE_ID], uTradeId);

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

	bool RestGetOrderIdByTradeId::ReceiveJson(const QJsonDocument& json, int nCode)
	{
		qDebug() << json;

		return false;
	}

}


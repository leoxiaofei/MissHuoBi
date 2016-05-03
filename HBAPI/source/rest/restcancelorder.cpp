#include "rest\restcancelorder.h"
#include "common\mapkv.h"

#include <QDebug>

namespace HBAPI
{

	void RestCancelOrder::SendRequest(CoinType eCoinType, 
		unsigned int uOrderId, MarketType eMarketType)
	{
		MapKV mapParams;
		mapParams.insert(szRestKName[RK_COIN_TYPE], eCoinType);
		mapParams.insert(szRestKName[RK_ID], uOrderId);

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

	bool RestCancelOrder::ReceiveJson(const QJsonDocument& json)
	{
		qDebug() << json;

		return false;
	}

}


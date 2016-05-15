#include "rest\restgetloans.h"
#include "common\mapkv.h"

#include <QDebug>

namespace HBAPI
{

	void RestGetLoans::SendRequest(MarketType eMarketType)
	{
		MapKV mapParams;

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

	bool RestGetLoans::ReceiveJson(const QJsonDocument& json, int nCode)
	{
		qDebug() << json;

		return false;
	}

}


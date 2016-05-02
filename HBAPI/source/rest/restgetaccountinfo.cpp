#include "rest\restgetaccountinfo.h"
#include "common\mapkv.h"

#include <QDebug>

namespace HBAPI
{

	void RestGetAccountInfo::SendRequest(MarketType eMarketType)
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

	bool RestGetAccountInfo::ReceiveJson(const QJsonObject& json)
	{
		qDebug() << json;

		return false;
	}

}


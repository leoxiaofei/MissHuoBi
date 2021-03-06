#include "rest\restgetwithdrawcoinresult.h"
#include "common\mapkv.h"

#include <QDebug>

namespace HBAPI
{

	void RestGetWithdrawCoinResult::SendRequest(
		unsigned int uWithdrawCoinId, MarketType eMarketType)
	{
		MapKV mapParams;
		mapParams.insert(szRestKName[RK_WITHDRAW_COIN_ID], uWithdrawCoinId);

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

	bool RestGetWithdrawCoinResult::ReceiveJson(const QJsonDocument& json, int nCode)
	{
		qDebug() << json;

		return false;
	}

}


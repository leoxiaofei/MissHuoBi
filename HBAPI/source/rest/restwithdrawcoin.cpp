#include "rest\restwithdrawcoin.h"
#include "common\mapkv.h"

#include <QDebug>

namespace HBAPI
{

	void RestWithdrawCoin::SendRequest(CoinType eCoinType, 
		const QString& strWithdrawAddress, 
		const double& dWithdrawAmount, MarketType eMarketType)
	{
		MapKV mapParams;
		mapParams.insert(szRestKName[RK_COIN_TYPE], eCoinType);
		mapParams.insert(szRestKName[RK_WITHDRAW_ADDRESS], strWithdrawAddress);
		mapParams.insert(szRestKName[RK_WITHDRAW_AMOUNT], dWithdrawAmount);

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

	bool RestWithdrawCoin::ReceiveJson(const QJsonDocument& json, int nCode)
	{
		qDebug() << json;

		return false;
	}

}


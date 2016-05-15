#include "rest\restbuy.h"
#include "common\mapkv.h"
#include "common\traderesult.h"
#include "tools\mspool.hpp"

#include <QDebug>
#include <QJsonDocument>

namespace HBAPI
{
	typedef MsPool<class Tag, TradeResult> MPTR;

	void RestBuy::SendRequest(CoinType eCoinType, const double& dPrice, 
		const double& dAmount, MarketType eMarketType)
	{
		MapKV mapParams;

		mapParams.insert(szRestKName[RK_COIN_TYPE], eCoinType);
		mapParams.insert(szRestKName[RK_PRICE], dPrice);
		mapParams.insert(szRestKName[RK_AMOUNT], QString::number(dAmount, 'f', 4));

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

	bool RestBuy::ReceiveJson(const QJsonDocument& json, int nCode)
	{
		qDebug() << json;

		QSharedPointer<TradeResult> ptTradeResult(MPTR::New(), &MPTR::Free);

		if (nCode == 0)
		{
			ParseTradeResult(json, *ptTradeResult);
		}
		else
		{
			ptTradeResult->bResult = false;
		}

		emit signal_Receive(ptTradeResult);

		return true;
	}

}


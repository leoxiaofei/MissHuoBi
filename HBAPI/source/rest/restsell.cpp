#include "rest\restsell.h"
#include "common\mapkv.h"
#include "tools\mspool.hpp"
#include "common\traderesult.h"

#include <QDebug>

namespace HBAPI
{
	typedef MsPool<class Tag, TradeResult> MPTR;

	void RestSell::SendRequest(CoinType eCoinType, const double& dPrice,
		const double& dAmount, MarketType eMarketType)
	{
		MapKV mapParams;

		mapParams.insert(szRestKName[RK_COIN_TYPE], eCoinType);
		mapParams.insert(szRestKName[RK_PRICE], dPrice);
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

	bool RestSell::ReceiveJson(const QJsonDocument& json, int nCode)
	{
		///{"id":1242384756,"result":"success"}
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


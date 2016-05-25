#include "rest\restorderinfo.h"
#include "common\mapkv.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

namespace HBAPI
{
	namespace
	{
		enum ElemText {
			ET_ID,
			ET_TYPE,
			ET_ORDER_PRICE,
			ET_ORDER_AMOUNT,
			ET_PROCESSED_PRICE,
			ET_PROCESSED_AMOUNT,
			ET_VOT,
			ET_FEE,
			ET_TOTAL,
			ET_STATUS,
		};

		const char* szElemText[] =
		{
			"id",
			"type",
			"order_price",
			"order_amount",
			"processed_price",
			"processed_amount",
			"vot",
			"fee",
			"total",
			"status",
		};

	}

	void RestOrderInfo::SendRequest(CoinType eCoinType, unsigned int uOrderId, MarketType eMarketType)
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

	bool RestOrderInfo::ReceiveJson(const QJsonDocument& json, int nCode)
	{
		qDebug() << json;

		QJsonObject jsInfo = json.object();

		OrderInfo* pOrderInfo = new OrderInfo;
		pOrderInfo->nId = jsInfo[szElemText[ET_ID]].toInt();
		pOrderInfo->eType = static_cast<OrderType>(jsInfo[szElemText[ET_TYPE]].toInt());
		pOrderInfo->dOrderPrice = jsInfo[szElemText[ET_ORDER_PRICE]].toDouble();
		pOrderInfo->dOrderAmount = jsInfo[szElemText[ET_ORDER_AMOUNT]].toDouble();
		pOrderInfo->dProcessedPrice = jsInfo[szElemText[ET_PROCESSED_PRICE]].toDouble();
		pOrderInfo->dProcessedAmount = jsInfo[szElemText[ET_PROCESSED_AMOUNT]].toDouble();
		pOrderInfo->dVot = jsInfo[szElemText[ET_VOT]].toDouble();
		pOrderInfo->dFee = jsInfo[szElemText[ET_FEE]].toDouble();
		pOrderInfo->dTotal = jsInfo[szElemText[ET_TOTAL]].toDouble();
		pOrderInfo->eStatus = static_cast<OrderStatus>(jsInfo[szElemText[ET_STATUS]].toInt());

		emit signal_Receive(QSharedPointer<OrderInfo>(pOrderInfo));

		return true;
	}

}


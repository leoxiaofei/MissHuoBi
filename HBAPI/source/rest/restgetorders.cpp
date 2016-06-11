#include "rest\restgetorders.h"
#include "common\mapkv.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

namespace HBAPI
{
	namespace
	{
		enum ElemText { ET_ORDER_TIME, ET_ORDER_AMOUNT, ET_ORDER_PRICE, ET_TYPE, ET_ID, ET_PROCESSED_AMOUNT };

		const char* szElemText[] =
		{
			"order_time",
			"order_amount",
			"order_price",
			"type",
			"id",
			"processed_amount",
		};
	}

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

		QList<OrdersData> listOrdersData;

		OrdersData od;

		QJsonArray jaOrders = json.array();
		for (QJsonArray::const_iterator citor = jaOrders.constBegin();
			citor != jaOrders.constEnd(); ++citor)
		{
			QJsonObject joOrder = citor->toObject();

			od.nId = joOrder[szElemText[ET_ID]].toInt();
			od.eType = static_cast<OrderType>(joOrder[szElemText[ET_TYPE]].toInt());
			od.dOrderPrice = joOrder[szElemText[ET_ORDER_PRICE]].toVariant().toDouble();
			od.dOrderAmount = joOrder[szElemText[ET_ORDER_AMOUNT]].toVariant().toDouble();
			od.dProcessedAmount = joOrder[szElemText[ET_PROCESSED_AMOUNT]].toVariant().toDouble();
			od.dtOrderTime = QDateTime::fromTime_t(joOrder[szElemText[ET_ORDER_TIME]].toInt());

			listOrdersData.append(od);
		}

		emit signal_Receive(listOrdersData);

		return true;
	}

}


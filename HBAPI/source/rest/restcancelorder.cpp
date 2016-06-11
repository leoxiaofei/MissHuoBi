#include "rest\restcancelorder.h"
#include "common\mapkv.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

namespace HBAPI
{
	namespace
	{
		enum ElemText { ET_RESULT };

		const char* szElemText[] =
		{
			"result",
		};
	}

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

	bool RestCancelOrder::ReceiveJson(const QJsonDocument& json, int nCode)
	{
		qDebug() << json;

		QJsonObject obj = json.object();

		bool bSuccess = obj[szElemText[ET_RESULT]].toString() == "success";

		emit signal_Receive(bSuccess);

		return true;
	}

}


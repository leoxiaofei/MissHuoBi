#include "common\traderesult.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QVariant>

namespace HBAPI
{
	namespace
	{
		enum ElemText { ET_ID, ET_RESULT };

		const char* szElemText[] =
		{
			"id",
			"result",
		};

	}


	void ParseTradeResult(const QJsonDocument& json, TradeResult& tTradeResult)
	{
		QJsonObject obj = json.object();
		tTradeResult.uOrderId = obj[szElemText[ET_ID]].toVariant().toUInt();
		tTradeResult.bResult = obj[szElemText[ET_RESULT]].toString() == "success";
	}

}

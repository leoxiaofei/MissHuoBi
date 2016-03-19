#include "tradesdata.h"
#include "misshbfunc.h"
#include "misshbdef.h"

#include <QJsonArray>
#include <QJsonObject>

namespace HBAPI
{

void ParseTradesData(const QJsonObject& json, QVector<TradesData>& vecTradesData)
{
	QJsonArray jaSubPrice = json[szAttributeName[AN_PRICE]].toArray();
	QJsonArray jaSubTime = json[szAttributeName[AN_TIME]].toArray();
	QJsonArray jaSubAmount = json[szAttributeName[AN_AMOUNT]].toArray();
	QJsonArray jaSubDirection = json[szAttributeName[AN_DIRECTION]].toArray();

	vecTradesData.resize(jaSubPrice.size());

	for (int ix = 0; ix != vecTradesData.size(); ++ix)
	{
		TradesData& ad = vecTradesData[ix];

		ad.rPrice = GetRationalValue(jaSubPrice[ix]);
		ad.tTime = jaSubTime[ix].toInt();
		ad.rAmount = GetRationalValue(jaSubAmount[ix]);
		ad.eDirection = static_cast<DirectionType>(jaSubDirection[ix].toInt());
	}
}

}

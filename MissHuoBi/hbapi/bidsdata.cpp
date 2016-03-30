#include "bidsdata.h"
#include "misshbdef.h"
#include "misshbfunc.h"

#include <QJsonArray>
#include <QJsonObject>


namespace HBAPI
{

void ParseBidsData(const QJsonObject& json, QVector<BidsData>& vecBidsData)
{
	QJsonArray jaSubPrice = json[szAttributeName[AN_PRICE]].toArray();
	QJsonArray jaSubLevel = json[szAttributeName[AN_LEVEL]].toArray();
	QJsonArray jaSubAmount = json[szAttributeName[AN_AMOUNT]].toArray();
	QJsonArray jaSubAccuAmount = json[szAttributeName[AN_ACCUAMOUNT]].toArray();

	vecBidsData.resize(jaSubPrice.size());

	for (int ix = 0; ix != vecBidsData.size(); ++ix)
	{
		BidsData& bd = vecBidsData[ix];

		bd.dPrice = jaSubPrice[ix].toDouble();
		bd.dLevel = jaSubLevel[ix].toDouble();
		bd.dAmount = jaSubAmount[ix].toDouble();
		bd.dAccuAmount = jaSubAccuAmount[ix].toDouble();
	}
}



}

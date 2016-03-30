#include "asksdata.h"
#include "misshbdef.h"
#include "misshbfunc.h"

#include <QJsonArray>
#include <QJsonObject>

namespace HBAPI
{

	void ParseAsksData(const QJsonObject& json, QVector<AsksData>& vecAsksData)
	{
		QJsonArray jaSubPrice = json[szAttributeName[AN_PRICE]].toArray();
		QJsonArray jaSubLevel = json[szAttributeName[AN_LEVEL]].toArray();
		QJsonArray jaSubAmount = json[szAttributeName[AN_AMOUNT]].toArray();
		QJsonArray jaSubAccuAmount = json[szAttributeName[AN_ACCUAMOUNT]].toArray();

		vecAsksData.resize(jaSubPrice.size());

		for (int ix = 0; ix != vecAsksData.size(); ++ix)
		{
			AsksData& ad = vecAsksData[ix];

			ad.dPrice = jaSubPrice[ix].toDouble();
			ad.dLevel = jaSubLevel[ix].toDouble();
			ad.dAmount = jaSubAmount[ix].toDouble();
			ad.dAccuAmount = jaSubAccuAmount[ix].toDouble();
		}
	}

}


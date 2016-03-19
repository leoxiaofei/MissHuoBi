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

			ad.rPrice = GetRationalValue(jaSubPrice[ix]);
			ad.nLevel = jaSubLevel[ix].toInt();
			ad.rAmount = GetRationalValue(jaSubAmount[ix]);
			ad.rAccuAmount = GetRationalValue(jaSubAccuAmount[ix]);
		}
	}

}


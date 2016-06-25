#include "common\klinedata.h"
#include "common\misshbfunc.h"
#include "common\misshbdef.h"

#include <QJsonObject>
#include <QJsonArray>


namespace HBAPI
{

void ParseKLineCylinder(const QJsonObject& json, KLineCylinder& cylinder)
{
	cylinder.tTime = json[szAttributeName[AN_TIME]].toDouble();
	cylinder.dPriceOpen = json[szAttributeName[AN_PRICEOPEN]].toDouble();
	cylinder.dPriceHigh = json[szAttributeName[AN_PRICEHIGH]].toDouble();
	cylinder.dPriceLow = json[szAttributeName[AN_PRICELOW]].toDouble();
	cylinder.dPriceLast = json[szAttributeName[AN_PRICELAST]].toDouble();
	cylinder.dAmount = json[szAttributeName[AN_AMOUNT]].toDouble();
	cylinder.dVolume = json[szAttributeName[AN_VOLUME]].toDouble();
	cylinder.nCount = json[szAttributeName[AN_COUNT]].toInt();
}

void ParseKLineCylinder(const QJsonObject& json, QVector<KLineCylinder>& vecCylinder)
{
	QJsonArray jaSubTime = json[szAttributeName[AN_TIME]].toArray();
	QJsonArray jaSubPriceOpen = json[szAttributeName[AN_PRICEOPEN]].toArray();
	QJsonArray jaSubPriceHigh = json[szAttributeName[AN_PRICEHIGH]].toArray();
	QJsonArray jaSubPriceLow = json[szAttributeName[AN_PRICELOW]].toArray();
	QJsonArray jaSubPriceLast = json[szAttributeName[AN_PRICELAST]].toArray();
	QJsonArray jaSubAmount = json[szAttributeName[AN_AMOUNT]].toArray();
	QJsonArray jaSubVolume = json[szAttributeName[AN_VOLUME]].toArray();
	QJsonArray jaSubCount = json[szAttributeName[AN_COUNT]].toArray();

	vecCylinder.resize(jaSubTime.size());

	for (int ix = 0; ix != vecCylinder.size(); ++ix)
	{
		KLineCylinder& cylinder = vecCylinder[ix];

		cylinder.tTime = jaSubTime[ix].toDouble();
		cylinder.dPriceOpen = jaSubPriceOpen[ix].toDouble();
		cylinder.dPriceHigh = jaSubPriceHigh[ix].toDouble();
		cylinder.dPriceLow = jaSubPriceLow[ix].toDouble();
		cylinder.dPriceLast = jaSubPriceLast[ix].toDouble();
		cylinder.dAmount = jaSubAmount[ix].toDouble();
		cylinder.dVolume = jaSubVolume[ix].toDouble();
		cylinder.nCount = jaSubCount[ix].toInt();
	}

}

void ParseKLineData(const QJsonObject& json, KLineData& kLineData)
{
	kLineData.eSymbolId = GetSymbolIdType(json[szAttributeName[AN_SYMBOLID]].toString());
	kLineData.ePeriod = GetPeriodType(json[szAttributeName[AN_PERIOD]].toString());

	ParseKLineCylinder(json, kLineData.vecCylinder);
}

void ParseLastKLineData(const QJsonObject& json, LastKLineData& lastKLineData)
{
	lastKLineData.eSymbolId = GetSymbolIdType(json[szAttributeName[AN_SYMBOLID]].toString());
	lastKLineData.ePeriod = GetPeriodType(json[szAttributeName[AN_PERIOD]].toString());

	ParseKLineCylinder(json, lastKLineData.cylinder);
}

}

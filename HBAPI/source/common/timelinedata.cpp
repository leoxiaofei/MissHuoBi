#include "common/timelinedata.h"
#include "common/misshbdef.h"
#include "common/misshbfunc.h"

#include <QJsonArray>
#include <QJsonObject>

namespace HBAPI
{

void ParseTimeLineCylinder(const QJsonObject& json, TimeLineCylinder& cylinder)
{
	cylinder.tTime = json[szAttributeName[AN_TIME]].toInt();
	cylinder.dPriceLast = json[szAttributeName[AN_PRICELAST]].toDouble();
	cylinder.dAmount = json[szAttributeName[AN_AMOUNT]].toDouble();
	cylinder.dVolume = json[szAttributeName[AN_VOLUME]].toDouble();
	cylinder.nCount = json[szAttributeName[AN_COUNT]].toDouble();
}

void ParseTimeLineCylinder(const QJsonObject& json, QVector<TimeLineCylinder>& vecCylinder)
{
	QJsonArray jaSubTime = json[szAttributeName[AN_TIME]].toArray();
	QJsonArray jaSubPriceLast = json[szAttributeName[AN_PRICELAST]].toArray();
	QJsonArray jaSubAmount = json[szAttributeName[AN_AMOUNT]].toArray();
	QJsonArray jaSubVolume = json[szAttributeName[AN_VOLUME]].toArray();
	QJsonArray jaSubCount = json[szAttributeName[AN_COUNT]].toArray();

	vecCylinder.resize(jaSubTime.size());

	for (int ix = 0; ix != vecCylinder.size(); ++ix)
	{
		TimeLineCylinder& cylinder = vecCylinder[ix];

		cylinder.tTime = jaSubTime[ix].toDouble();
		cylinder.dPriceLast = jaSubPriceLast[ix].toDouble();
		cylinder.dAmount = jaSubAmount[ix].toDouble();
		cylinder.dVolume = jaSubVolume[ix].toDouble();
		cylinder.nCount = jaSubCount[ix].toInt();
	}
}

void ParseTimeLineCylinder(const QJsonObject& json, TimeLineData& timeLineData)
{
	timeLineData.eSymbolId = GetSymbolIdType(json[szAttributeName[AN_SYMBOLID]].toString());
	ParseTimeLineCylinder(json, timeLineData.vecCylinder);
}

void ParseTimeLineCylinder(const QJsonObject& json, LastTimeLineData& lastTimeLineData)
{
	lastTimeLineData.eSymbolId = GetSymbolIdType(json[szAttributeName[AN_SYMBOLID]].toString());
	ParseTimeLineCylinder(json, lastTimeLineData.cylinder);
}

}

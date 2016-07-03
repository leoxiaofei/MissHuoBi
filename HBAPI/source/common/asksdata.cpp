#include "common/asksdata.h"
#include "common/misshbdef.h"
#include "common/misshbfunc.h"

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

	void ParseAskDepthData(const QJsonObject& json, QList<AskDepthData>& listDepthData)
	{
		QJsonArray jaSubPrice = json[szAttributeName[AN_ASKPRICE]].toArray();
		QJsonArray jaSubAmount = json[szAttributeName[AN_ASKAMOUNT]].toArray();
		QJsonArray jaSubTotal = json[szAttributeName[AN_ASKTOTAL]].toArray();

		listDepthData.clear();
		for (int ix = 0; ix != jaSubPrice.size(); ++ix)
		{
			AskDepthData add;

			add.dPrice = jaSubPrice[ix].toDouble();
			add.dAmount = jaSubAmount[ix].toDouble();
			add.dTotal = jaSubTotal[ix].toDouble();

			listDepthData.append(add);
		}
	}

	void ParseAskInsertData(const QJsonObject& json, QVector<AskInsertData>& vecAskInsertData)
	{
		QJsonArray jaSubPrice = json[szAttributeName[AN_PRICE]].toArray();
		QJsonArray jaSubAmount = json[szAttributeName[AN_AMOUNT]].toArray();
		QJsonArray jaSubRow = json[szAttributeName[AN_ROW]].toArray();

		vecAskInsertData.resize(jaSubPrice.size());

		for (int ix = 0; ix != vecAskInsertData.size(); ++ix)
		{
			AskInsertData& ad = vecAskInsertData[ix];

			ad.dPrice = jaSubPrice[ix].toDouble();
			ad.dAmount = jaSubAmount[ix].toDouble();
			ad.nRow = jaSubRow[ix].toInt();
		}
	}

	void ParsAskDeleteData(const QJsonArray& json, QVector<AskDeleteData>& vecAskDeleteData)
	{
		vecAskDeleteData.resize(json.size());

		for (int ix = 0; ix != vecAskDeleteData.size(); ++ix)
		{
			AskDeleteData& ad = vecAskDeleteData[ix];

			ad.nRow = json[ix].toInt();
		}
	}

	void ParseAskUpdateData(const QJsonObject& json, QVector<AskUpdateData>& vecAskUpdateData)
	{
		QJsonArray jaSubPrice = json[szAttributeName[AN_PRICE]].toArray();
		QJsonArray jaSubAmount = json[szAttributeName[AN_AMOUNT]].toArray();
		QJsonArray jaSubRow = json[szAttributeName[AN_ROW]].toArray();

		vecAskUpdateData.resize(jaSubPrice.size());

		for (int ix = 0; ix != vecAskUpdateData.size(); ++ix)
		{
			AskUpdateData& ad = vecAskUpdateData[ix];

			ad.dPrice = jaSubPrice[ix].toDouble();
			ad.dAmount = jaSubAmount[ix].toDouble();
			ad.nRow = jaSubRow[ix].toInt();
		}
	}

	bool AskDepthData::operator==(const AskDepthData& other) const
	{
		return qFuzzyCompare(this->dPrice, other.dPrice)
			&& qFuzzyCompare(this->dAmount, other.dAmount)
			&& qFuzzyCompare(this->dTotal, other.dTotal);
	}

}


#include "common/bidsdata.h"
#include "common/misshbdef.h"
#include "common/misshbfunc.h"

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



void ParseBidInsertData(const QJsonObject& json, QVector<BidInsertData>& vecBidInsertData)
{
	QJsonArray jaSubPrice = json[szAttributeName[AN_PRICE]].toArray();
	QJsonArray jaSubAmount = json[szAttributeName[AN_AMOUNT]].toArray();
	QJsonArray jaSubRow = json[szAttributeName[AN_ROW]].toArray();

	vecBidInsertData.resize(jaSubPrice.size());

	for (int ix = 0; ix != vecBidInsertData.size(); ++ix)
	{
		BidInsertData& bd = vecBidInsertData[ix];

		bd.dPrice = jaSubPrice[ix].toDouble();
		bd.dAmount = jaSubAmount[ix].toDouble();
		bd.nRow = jaSubRow[ix].toInt();
	}
}

void ParseBidDeleteData(const QJsonArray& json, QVector<BidDeleteData>& vecBidDeleteData)
{
	vecBidDeleteData.resize(json.size());

	for (int ix = 0; ix != vecBidDeleteData.size(); ++ix)
	{
		BidDeleteData& bd = vecBidDeleteData[ix];

		bd.nRow = json[ix].toInt();
	}
}

void ParseBidUpdateData(const QJsonObject& json, QVector<BidUpdateData>& vecBidUpdateData)
{
	QJsonArray jaSubPrice = json[szAttributeName[AN_PRICE]].toArray();
	QJsonArray jaSubAmount = json[szAttributeName[AN_AMOUNT]].toArray();
	QJsonArray jaSubRow = json[szAttributeName[AN_ROW]].toArray();

	vecBidUpdateData.resize(jaSubPrice.size());

	for (int ix = 0; ix != vecBidUpdateData.size(); ++ix)
	{
		BidUpdateData& bd = vecBidUpdateData[ix];

		bd.dPrice = jaSubPrice[ix].toDouble();
		bd.dAmount = jaSubAmount[ix].toDouble();
		bd.nRow = jaSubRow[ix].toInt();
	}
}

}

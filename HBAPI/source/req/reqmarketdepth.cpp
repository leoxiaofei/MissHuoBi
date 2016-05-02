#include "req/reqmarketdepth.h"
#include "tools/mspool.hpp"
#include "common/marketdepthdata.h"

#include <QJsonObject>

namespace HBAPI
{
	typedef MsPool<class Tag, MarketDepthData> MPMDD;

ReqMarketDepth::ReqMarketDepth()
{

}

ReqMarketDepth::~ReqMarketDepth()
{

}

int ReqMarketDepth::SendRequest(SymbolIdType eSymbolId, PercentType ePercentType)
{
	QJsonObject json;
	json.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
	json.insert(szAttributeName[AN_PERCENT], szPercentType[ePercentType]);
	return SendJson(json);
}

bool ReqMarketDepth::ReceiveJson(const QJsonObject& json)
{
	QSharedPointer<MarketDepthData> ptMarketDepthData(MPMDD::New(), &MPMDD::Free);

	ParseMarketDepthData(json, *ptMarketDepthData);

	emit signal_Receive(ptMarketDepthData);

	return true;
}

}

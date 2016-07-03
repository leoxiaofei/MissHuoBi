#include "req/reqmarketdepthtop.h"
#include "common/marketdepthtopdata.h"
#include "tools/mspool.hpp"

#include <QJsonObject>

namespace HBAPI
{
	typedef MsPool<class Tag, MarketDepthTopData> MPMDTD;

ReqMarketDepthTop::ReqMarketDepthTop()
{

}

ReqMarketDepthTop::~ReqMarketDepthTop()
{

}

int ReqMarketDepthTop::SendRequest(SymbolIdType eSymbolId)
{
	QJsonObject json;
	json.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
	return SendJson(json);
}

bool ReqMarketDepthTop::ReceiveJson(const QJsonObject& json)
{
	QSharedPointer<MarketDepthTopData> ptMarketDepthTopData(MPMDTD::New(), &MPMDTD::Free);

	ParseMarketDepthTopData(json, *ptMarketDepthTopData);

	emit signal_Receive(ptMarketDepthTopData);

	return true;
}

}

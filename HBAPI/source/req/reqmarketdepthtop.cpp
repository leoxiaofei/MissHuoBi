#include "req/reqmarketdepthtop.h"
#include <QJsonObject>


namespace HBAPI
{


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
	return true;
}

}

#include "msg/msgmarketdetail.h"
#include "tools/mspool.hpp"
#include "common/misshbfunc.h"

#include <QJsonObject>

namespace HBAPI
{
	typedef MsPool<class Tag, MarketDetailBill> MPMDB;

Subscriber MsgMarketDetail::GetSubscriber(SymbolIdType eSymbolId, PushType ePushType)
{
	QJsonObject js;
	js.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
	js.insert(szAttributeName[AN_PUSHTYPE], szPushType[ePushType]);

	return Subscriber(MsgType(), js);
}

bool MsgMarketDetail::ReceiveJson(const QJsonObject& joPayload)
{
	QSharedPointer<MarketDetailBill> ptTradeDetail (MPMDB::New(), &MPMDB::Free);

	ptTradeDetail->eSymbolId = GetSymbolIdType(joPayload[szAttributeName[AN_SYMBOLID]].toString());
	ptTradeDetail->dPriceNew = joPayload[szAttributeName[AN_PRICENEW]].toDouble();
	ptTradeDetail->dPriceOpen = joPayload[szAttributeName[AN_PRICEOPEN]].toDouble();
	ptTradeDetail->dPriceHigh = joPayload[szAttributeName[AN_PRICEHIGH]].toDouble();
	ptTradeDetail->dPriceLow = joPayload[szAttributeName[AN_PRICELOW]].toDouble();
	ptTradeDetail->dPriceLast = joPayload[szAttributeName[AN_PRICELAST]].toDouble();
	ptTradeDetail->dPriceAverage = joPayload[szAttributeName[AN_PRICEAVERAGE]].toDouble();
	ptTradeDetail->dAmount = joPayload[szAttributeName[AN_AMOUNT]].toDouble();
	ptTradeDetail->dTotalAmount = joPayload[szAttributeName[AN_TOTALAMOUNT]].toDouble();
	ptTradeDetail->dTotalVolume = joPayload[szAttributeName[AN_TOTALVOLUME]].toDouble();
	ptTradeDetail->dUpdownVolume = joPayload[szAttributeName[AN_UPDOWNVOLUME]].toDouble();
	ptTradeDetail->dUpdownRatio = joPayload[szAttributeName[AN_UPDOWNRATIO]].toDouble();
	ptTradeDetail->dTurnVolume = joPayload[szAttributeName[AN_TURNVOLUME]].toDouble();
	ptTradeDetail->dTurnoverRate = joPayload[szAttributeName[AN_TURNOVERRATE]].toDouble();
	ptTradeDetail->dCommissionRatio = joPayload[szAttributeName[AN_COMMISSIONRATIO]].toDouble();
	ptTradeDetail->dPoor = joPayload[szAttributeName[AN_POOR]].toDouble();
	ptTradeDetail->dOuterDisc = joPayload[szAttributeName[AN_OUTERDISC]].toDouble();
	ptTradeDetail->dInnerDisc = joPayload[szAttributeName[AN_INNERDISC]].toDouble();
	ptTradeDetail->dVolumeRatio = joPayload[szAttributeName[AN_VOLUMERATIO]].toDouble();

	ParseBidsData(joPayload[szAttributeName[AN_BIDS]].toObject(), ptTradeDetail->vecBidsData);
	ParseAsksData(joPayload[szAttributeName[AN_ASKS]].toObject(), ptTradeDetail->vecAsksData);
	ParseTradesData(joPayload[szAttributeName[AN_TRADES]].toObject(), ptTradeDetail->vecTradesData);

	emit signal_Receive(ptTradeDetail);

	return true;
}

}

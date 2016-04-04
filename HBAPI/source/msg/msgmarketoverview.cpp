#include "msg/msgmarketoverview.h"
#include "tools/mspool.hpp"
#include "common/misshbfunc.h"

#include <QJsonObject>
#include <QSharedPointer>

namespace HBAPI
{
	typedef MsPool<class Tag, MarketOverviewData> MPMDTDD;

	MsgMarketOverview::MsgMarketOverview()
	{
		
	}

	MsgMarketOverview::~MsgMarketOverview()
	{

	}

	Subscriber MsgMarketOverview::GetSubscriber(SymbolIdType eSymbolId, PushType ePushType)
	{
		QJsonObject js;
		js.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
		js.insert(szAttributeName[AN_PUSHTYPE], szPushType[ePushType]);

		return Subscriber(MsgType(), js);
	}

	bool MsgMarketOverview::ReceiveJson(const QJsonObject& joPayload)
	{
		QSharedPointer<MarketOverviewData> ptMarketOverviewData(MPMDTDD::New(), &MPMDTDD::Free);

		ptMarketOverviewData->eSymbolId = GetSymbolIdType(joPayload[szAttributeName[AN_SYMBOLID]].toString());
		ptMarketOverviewData->dPriceNew = joPayload[szAttributeName[AN_PRICENEW]].toDouble();
		ptMarketOverviewData->dPriceOpen = joPayload[szAttributeName[AN_PRICEOPEN]].toDouble();
		ptMarketOverviewData->dPriceHigh = joPayload[szAttributeName[AN_PRICEHIGH]].toDouble();
		ptMarketOverviewData->dPriceLow = joPayload[szAttributeName[AN_PRICELOW]].toDouble();
		ptMarketOverviewData->dPriceAsk = joPayload[szAttributeName[AN_PRICEASK]].toDouble();
		ptMarketOverviewData->dPriceBid = joPayload[szAttributeName[AN_PRICEBID]].toDouble();
		ptMarketOverviewData->dTotalVolume = joPayload[szAttributeName[AN_TOTALVOLUME]].toDouble();
		ptMarketOverviewData->dTotalAmount = joPayload[szAttributeName[AN_TOTALAMOUNT]].toDouble();

		emit signal_Receive(ptMarketOverviewData);

		return true;
	}

}

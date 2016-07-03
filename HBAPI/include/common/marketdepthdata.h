#ifndef __MARKETDEPTHDATA_H__
#define __MARKETDEPTHDATA_H__

#include "misshbdef.h"
#include "asksdata.h"
#include "bidsdata.h"

namespace HBAPI
{
	class HBAPI_EXPORT MarketDepthData
	{
	public:
		SymbolIdType			eSymbolId;
		PercentType				ePercent;
		time_t					tTime;
		quint64					uVersion;
		QList<AskDepthData>		listAskDepthData;
		QList<BidDepthData>		listBidDepthData;
	};

	void ParseMarketDepthData(const QJsonObject& joPayload, MarketDepthData& mdd);

	class HBAPI_EXPORT MarketDepthDiffData
	{
	public:
		SymbolIdType				eSymbolId;
		PercentType					ePercentType;
		quint64						uVersion;
		quint64						uVersionOld;
		QVector<AskInsertData>		vecAskInsertData;
		QVector<AskDeleteData>		vecAskDeleteData;
		QVector<AskUpdateData>		vecAskUpdateData;
		QVector<BidInsertData>		vecBidInsertData;
		QVector<BidDeleteData>		vecBidDeleteData;
		QVector<BidUpdateData>		vecBidUpdateData;
	};

}

#endif // __MARKETDEPTHDATA_H__

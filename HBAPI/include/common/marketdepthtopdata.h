#ifndef __MARKETDEPTHTOPDATA_H__
#define __MARKETDEPTHTOPDATA_H__

#include "misshbdef.h"
#include "asksdata.h"
#include "bidsdata.h"

namespace HBAPI
{
	class HBAPI_EXPORT MarketDepthTopData
	{
	public:
		SymbolIdType			eSymbolId;
		time_t					tTime;
		quint64					uVersion;
		QList<AskDepthData>		listAskDepthData;
		QList<BidDepthData>		listBidDepthData;
	};

	void ParseMarketDepthTopData(const QJsonObject& joPayload, MarketDepthTopData& mdtd);

	class HBAPI_EXPORT MarketDepthTopDiffData
	{
	public:
		SymbolIdType				eSymbolId;
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

#endif // __MARKETDEPTHTOPDATA_H__

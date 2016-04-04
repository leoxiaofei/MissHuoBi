#include "msg/msgtradedetail.h"
#include "tools/mspool.hpp"
#include "common/misshbfunc.h"

#include <QJsonObject>
#include <QSharedPointer>

namespace HBAPI
{
	typedef MsPool<class Tag, TradeDetailData> MPTDD;
	typedef MsPool<class Tag, TradeDetailBill> MPTDB;

	TradeDetailBill::~TradeDetailBill()
	{
		Free();
	}

	void TradeDetailBill::Resize(int nSize)
	{
		int nSpan = vecTradeDetailData.size() - nSize;
		if (nSpan > 0)
		{
			while (nSpan)
			{
				MPTDD::Free(vecTradeDetailData.takeLast());
				--nSpan;
			}
		}
		else if (nSpan < 0)
		{
			nSpan = qAbs(nSpan);
			while (nSpan)
			{
				vecTradeDetailData.append(MPTDD::New());
				--nSpan;
			}
		}
	}

	void TradeDetailBill::Free()
	{
		while (!vecTradeDetailData.isEmpty())
		{
			MPTDD::Free(vecTradeDetailData.takeLast());
		}
	}

	Subscriber HBAPI::MsgTradeDetail::GetSubscriber(SymbolIdType eSymbolId, PushType ePushType)
	{
		QJsonObject js;
		js.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
		js.insert(szAttributeName[AN_PUSHTYPE], szPushType[ePushType]);

		return Subscriber(MsgType(), js);
	}

	bool MsgTradeDetail::ReceiveJson(const QJsonObject& joPayload)
	{
		QSharedPointer<TradeDetailBill> ptTradeDetail(MPTDB::New(), &MPTDB::Free);

		ptTradeDetail->eSymbolId = GetSymbolIdType(joPayload[szAttributeName[AN_SYMBOLID]].toString());

		QJsonArray jaTradeId = joPayload[szAttributeName[AN_TRADEID]].toArray();
		QJsonArray jaPrice = joPayload[szAttributeName[AN_PRICE]].toArray();
		QJsonArray jaTime = joPayload[szAttributeName[AN_TIME]].toArray();
		QJsonArray jaAmount = joPayload[szAttributeName[AN_AMOUNT]].toArray();
		QJsonArray jaDirection = joPayload[szAttributeName[AN_DIRECTION]].toArray();
		QJsonArray jaTopBids = joPayload[szAttributeName[AN_TOPBIDS]].toArray();
		QJsonArray jaTopAsks = joPayload[szAttributeName[AN_TOPASKS]].toArray();

		ptTradeDetail->Resize(jaTradeId.size());

		for (int ix = 0; ix != ptTradeDetail->vecTradeDetailData.size(); ++ix)
		{
			TradeDetailData* pData = ptTradeDetail->vecTradeDetailData[ix];

			pData->nTradeId = jaTradeId[ix].toInt();
			pData->dPrice = jaPrice[ix].toDouble();
			pData->tTime = jaTime[ix].toInt();
			pData->dAmount = jaAmount[ix].toDouble();
			pData->eDirection = static_cast<DirectionType>(jaDirection[ix].toInt());

			ParseBidsData(jaTopBids[ix].toObject(), pData->vecTopBidsData);

			ParseAsksData(jaTopAsks[ix].toObject(), pData->vecTopAsksData);
		}

		return true;
	}

}

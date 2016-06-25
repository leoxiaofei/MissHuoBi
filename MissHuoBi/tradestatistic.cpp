#include "tradestatistic.h" 
#include "stattradedata.h"
#include "tools\mspool.hpp"
#include "msg\msgtradedetail.h"
#include "hbmarket.h"
#include "hbapihandle.h"
#include "tradedetailmodel.h"

#include <QPointer>

typedef MsPool<class Tag, StatTradeData> MPSTD;

using namespace HBAPI;

class TradeStatistic::Impl
{
public:
	Impl(QObject* parent)
		: mdTradeDetail(new TradeDetailModel(parent))
	{}
	QPointer<TradeDetailModel> mdTradeDetail;
};

TradeStatistic::TradeStatistic(QObject* parent)
	: QObject(parent)
	, m_pImpl(new Impl(this))
{
	Init();
}

TradeStatistic::~TradeStatistic()
{
}

void TradeStatistic::Init()
{
	MsgTradeDetail* pMsgTradeDetail =
		SHBAPI::Instance().GetMarket()->QueryMessage<MsgTradeDetail>();

	QObject::connect(pMsgTradeDetail, &MsgTradeDetail::signal_Receive,
		this, &TradeStatistic::slot_AddTradeDetai);
}

void TradeStatistic::StatTrade(const QVector<HBAPI::TradeDetailData*>& vecTrade)
{
	StatTradeData* pData = MPSTD::New();
	pData->Clear();

	for (QVector<HBAPI::TradeDetailData*>::const_iterator citor = vecTrade.cbegin();
		citor != vecTrade.cend(); ++citor)
	{
		HBAPI::TradeDetailData* pTrade = *citor;
		switch (pTrade->eDirection)
		{
		case HBAPI::DT_BUYING:
		case HBAPI::DT_BUYING2:
			pData->dBuyingAmount += pTrade->dAmount;
			++pData->dBuyingCount;
			break;
		case HBAPI::DT_SELLING:
		case HBAPI::DT_SELLIN2:
			pData->dSellingAmount += pTrade->dAmount;
			++pData->dSellingCount;
			break;
		default:
			break;
		}

		pData->dAvePrice += pTrade->dPrice;
		pData->dMaxPrice = qMax(pData->dMaxPrice, pTrade->dPrice);
		pData->dMinPrice = qMin(pData->dMinPrice, pTrade->dPrice);
	}

	pData->dAvePrice = pData->dAvePrice / vecTrade.size();

	emit signal_StatTradeData(QSharedPointer<StatTradeData>(pData, &MPSTD::Free));
}

void TradeStatistic::slot_AddTradeDetai(const QSharedPointer<HBAPI::TradeDetailBill>& ptTradeDetailBill)
{
	if (!ptTradeDetailBill->vecTradeDetailData.isEmpty())
	{
		StatTrade(ptTradeDetailBill->vecTradeDetailData);
		m_pImpl->mdTradeDetail->AddTradeDetai(ptTradeDetailBill);
	}
}

TradeDetailModel* TradeStatistic::GetTradeDetailModel()
{
	return m_pImpl->mdTradeDetail;
}

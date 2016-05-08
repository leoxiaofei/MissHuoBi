#include "marketboard.h"
#include "marketdepthmodel.h"
#include "hbapihandle.h"
#include "msg\msgmarketdepthdiff.h"
#include "hbmarket.h"
#include "req\reqmarketdepth.h"
#include "msg\msgmarketdepthtopdiff.h"
#include "req\reqmarketdepthtop.h"
#include "common\marketdepthtopdata.h"
#include "common\marketdepthdata.h"

#include <QSortFilterProxyModel>

using namespace HBAPI;

class MarketBoard::Impl
{
public:
	MarketDepthModel*	pMDM;

};

MarketBoard::MarketBoard(QWidget *parent)
	: QWidget(parent)
	, m_pImpl(new Impl)
{
	ui.setupUi(this);
	Init();
}

MarketBoard::~MarketBoard()
{

}

void MarketBoard::Init()
{
	m_pImpl->pMDM = new MarketDepthModel(this);
	QObject::connect(m_pImpl->pMDM, &MarketDepthModel::signal_ReloadMarketDepth,
		this, &MarketBoard::slot_ReloadMarketDepth);
	QObject::connect(m_pImpl->pMDM, &MarketDepthModel::signal_ReloadMarketDepthTop,
		this, &MarketBoard::slot_ReloadMarketDepthTop);

	MsgMarketDepthDiff* pMsgMarketDepthDiff =
		SHBAPI::Instance().GetMarket()->QueryMessage<MsgMarketDepthDiff>();

	QObject::connect(pMsgMarketDepthDiff, &MsgMarketDepthDiff::signal_Receive,
		m_pImpl->pMDM, &MarketDepthModel::slot_ReciMarketDepthDiffData);

	ReqMarketDepth* pReqMarketDepth =
		SHBAPI::Instance().GetMarket()->QueryRequest<ReqMarketDepth>();

	QObject::connect(pReqMarketDepth, &ReqMarketDepth::signal_Receive,
		m_pImpl->pMDM, &MarketDepthModel::slot_ReciMarketDepthData);

	MsgMarketDepthTopDiff* pMsgMarketDepthTopDiff =
		SHBAPI::Instance().GetMarket()->QueryMessage<MsgMarketDepthTopDiff>();

	QObject::connect(pMsgMarketDepthTopDiff, &MsgMarketDepthTopDiff::signal_Receive,
		m_pImpl->pMDM, &MarketDepthModel::slot_ReciMarketDepthTopDiffData);

	ReqMarketDepthTop* pReqMarketDepthTop =
		SHBAPI::Instance().GetMarket()->QueryRequest<ReqMarketDepthTop>();

	QObject::connect(pReqMarketDepthTop, &ReqMarketDepthTop::signal_Receive,
		m_pImpl->pMDM, &MarketDepthModel::slot_ReciMarketDepthTopData);


	QSortFilterProxyModel* pAskModel = new QSortFilterProxyModel(this);
	pAskModel->setSourceModel(m_pImpl->pMDM);
	pAskModel->setFilterFixedString("A");
	pAskModel->setFilterKeyColumn(MarketDepthModel::MD_D);
	ui.tvAsk->setModel(pAskModel);
	ui.tvAsk->hideColumn(MarketDepthModel::MD_D);

	QSortFilterProxyModel* pBidModel = new QSortFilterProxyModel(this);
	pBidModel->setSourceModel(m_pImpl->pMDM);
	pBidModel->setFilterFixedString("B");
	pBidModel->setFilterKeyColumn(MarketDepthModel::MD_D);
	ui.tvBid->setModel(pBidModel);
	ui.tvBid->hideColumn(MarketDepthModel::MD_D);

	ui.tvAsk->horizontalHeader()->setSectionResizeMode(MarketDepthModel::MD_PRICE, QHeaderView::Stretch);
	ui.tvAsk->horizontalHeader()->setSectionResizeMode(MarketDepthModel::MD_AMOUNT, QHeaderView::Stretch);
	ui.tvAsk->horizontalHeader()->setSectionResizeMode(MarketDepthModel::MD_TOTAL, QHeaderView::Stretch);

	ui.tvBid->horizontalHeader()->setSectionResizeMode(MarketDepthModel::MD_PRICE, QHeaderView::Stretch);
	ui.tvBid->horizontalHeader()->setSectionResizeMode(MarketDepthModel::MD_AMOUNT, QHeaderView::Stretch);
	ui.tvBid->horizontalHeader()->setSectionResizeMode(MarketDepthModel::MD_TOTAL, QHeaderView::Stretch);
}

MarketDepthModel* MarketBoard::GetMarketDepthModel()
{
	return m_pImpl->pMDM;
}

void MarketBoard::slot_ReloadMarketDepth()
{
	ReqMarketDepth* pReqMarketDepth =
		SHBAPI::Instance().GetMarket()->QueryRequest<ReqMarketDepth>();

	pReqMarketDepth->SendRequest(SIT_BTCCNY, HBAPI::PT_PERCENT100);
}

void MarketBoard::slot_ReloadMarketDepthTop()
{
	ReqMarketDepthTop* pReqMarketDepth =
		SHBAPI::Instance().GetMarket()->QueryRequest<ReqMarketDepthTop>();

	pReqMarketDepth->SendRequest(SIT_BTCCNY);
}


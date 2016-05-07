#include "misshuobi.h"

#include <QDebug>
#include <QUrl>
#include <QVariant>
#include <QJsonObject>
#include <functional>
#include <QTimer>
#include <QSortFilterProxyModel>
#include <QHeaderView>

#include "common\marketdepthdata.h"
#include "common\marketdepthtopdata.h"
#include "common\misshbdef.h"
#include "hbmarket.h"
#include "hbmarketlinker.h"
#include "hbrest.h"
#include "hbrestlinker.h"
#include "marketdepthmodel.h"
#include "msg\msgmarketdepthdiff.h"
#include "msg\msgmarketdepthtopdiff.h"
#include "msg\msgmarketoverview.h"
#include "msg\msgtradedetail.h"
#include "panelboard.h"
#include "req\reqmarketdepth.h"
#include "req\reqmarketdepthtop.h"
#include "req\reqmsgsubscribe.h"
#include "rest\restgetaccountinfo.h"
#include "rest\restgetnewdealorders.h"
#include "rest\restgetorders.h"
#include "tradedetailmodel.h"
#include "mscfgfile.h"

using namespace HBAPI;

class MissHuoBi::Impl
{
public:
	HbMarket*			pM;
	HbMarketLinker*		pML;

	HbRest*				pR;
	HbRestLinker*		pRL;

	MarketDepthModel*	pMDM;

};


MissHuoBi::MissHuoBi(QWidget *parent)
	: QMainWindow(parent)
	, m_pImpl(new Impl)
{
	ui.setupUi(this);
	Init();
}

void MissHuoBi::Init()
{
	MsCfgFile msCfg;
	msCfg.LoadFile("MsCfg.hb");

	m_pImpl->pR = new HbRest(this);
	m_pImpl->pRL = new HbRestLinker(this);
	m_pImpl->pR->SetSendFunc(std::bind(&HbRestLinker::PostData, m_pImpl->pRL, std::placeholders::_1));
	m_pImpl->pRL->SetRecvFunc(std::bind(&HbRest::ParserRequest, m_pImpl->pR, std::placeholders::_1, std::placeholders::_2));

	m_pImpl->pR->SetKey(msCfg.strAccessKey, msCfg.strSecretKey);
	m_pImpl->pRL->SetUrl(QUrl(msCfg.strRestUrl));

	m_pImpl->pM = new HbMarket(this);
	m_pImpl->pML = new HbMarketLinker(this);
	m_pImpl->pM->SetSendFunc(m_pImpl->pML->GetSendFunc());
	m_pImpl->pML->SetRecvFunc(std::bind(&HbMarket::ParserRequest, m_pImpl->pM, std::placeholders::_1),
		std::bind(&HbMarket::ParserMessage, m_pImpl->pM, std::placeholders::_1));

	m_pImpl->pML->SetUrl(QUrl(msCfg.strWebSocketUrl));

	QObject::connect(m_pImpl->pML, &HbMarketLinker::signal_Connected, this,
		&MissHuoBi::slot_Subscribe);
	//////////////////////////////////////////////////////////////////////////

	TradeDetailModel* pTradeModel = new TradeDetailModel(ui.tvTradeLog);

	ui.tvTradeLog->setModel(pTradeModel);
	ui.tvTradeLog->hideColumn(TradeDetailModel::TD_TRADEID);
	//ui.tvTradeLog->hideColumn(TradeDetailModel::TD_TIME);
	ui.tvTradeLog->horizontalHeader()->setSectionResizeMode(TradeDetailModel::TD_PRICE, QHeaderView::Stretch);
	ui.tvTradeLog->horizontalHeader()->setSectionResizeMode(TradeDetailModel::TD_AMOUNT, QHeaderView::Stretch);
	ui.tvTradeLog->horizontalHeader()->setSectionResizeMode(TradeDetailModel::TD_DIRECTION, QHeaderView::Stretch);

	m_pImpl->pMDM = new MarketDepthModel(this);
	QObject::connect(m_pImpl->pMDM, &MarketDepthModel::signal_ReloadMarketDepth, 
		this, &MissHuoBi::slot_ReloadMarketDepth);
	QObject::connect(m_pImpl->pMDM, &MarketDepthModel::signal_ReloadMarketDepthTop,
		this, &MissHuoBi::slot_ReloadMarketDepthTop);

	MsgMarketOverview* pMsgMarketDetail =
		m_pImpl->pM->QueryMessage<MsgMarketOverview>();

	QObject::connect(pMsgMarketDetail, &MsgMarketOverview::signal_Receive,
		ui.wgPanelBoard, &PanelBoard::slot_UpadePanel);

	MsgMarketDepthDiff* pMsgMarketDepthDiff =
		m_pImpl->pM->QueryMessage<MsgMarketDepthDiff>();

	QObject::connect(pMsgMarketDepthDiff, &MsgMarketDepthDiff::signal_Receive,
		m_pImpl->pMDM, &MarketDepthModel::slot_ReciMarketDepthDiffData);

	ReqMarketDepth* pReqMarketDepth =
		m_pImpl->pM->QueryRequest<ReqMarketDepth>();

	QObject::connect(pReqMarketDepth, &ReqMarketDepth::signal_Receive,
		m_pImpl->pMDM, &MarketDepthModel::slot_ReciMarketDepthData);

	MsgMarketDepthTopDiff* pMsgMarketDepthTopDiff =
		m_pImpl->pM->QueryMessage<MsgMarketDepthTopDiff>();

	QObject::connect(pMsgMarketDepthTopDiff, &MsgMarketDepthTopDiff::signal_Receive,
		m_pImpl->pMDM, &MarketDepthModel::slot_ReciMarketDepthTopDiffData);

	ReqMarketDepthTop* pReqMarketDepthTop =
		m_pImpl->pM->QueryRequest<ReqMarketDepthTop>();

	QObject::connect(pReqMarketDepthTop, &ReqMarketDepthTop::signal_Receive,
		m_pImpl->pMDM, &MarketDepthModel::slot_ReciMarketDepthTopData);

	
 	MsgTradeDetail* pMsgTradeDetail = m_pImpl->pM->QueryMessage<MsgTradeDetail>();

	QObject::connect(pMsgTradeDetail, &MsgTradeDetail::signal_Receive,
		pTradeModel, &TradeDetailModel::slot_AddTradeDetai);
	
	ui.wgMarketBoard->Init(m_pImpl->pMDM);

	QTimer::singleShot(500, this, &MissHuoBi::on_actionConnect_triggered);

	ui.dockLog->hide();
}

void MissHuoBi::closeEvent(QCloseEvent * ev)
{
	QEventLoop loop;
	QObject::connect(m_pImpl->pML, &HbMarketLinker::signal_Disconnected, &loop, &QEventLoop::quit);
	QTimer::singleShot(2000, &loop, &QEventLoop::quit);
	on_actionDisconnect_triggered();
	loop.exec(QEventLoop::ExcludeUserInputEvents);
}

MissHuoBi::~MissHuoBi()
{

}

void MissHuoBi::on_actionConnect_triggered()
{
	qDebug() << "on_actionConnect_triggered";
	m_pImpl->pML->Connect();
}

void MissHuoBi::on_actionDisconnect_triggered()
{
	qDebug() << "on_actionDisconnect_triggered";
	m_pImpl->pML->Disconnect();
}

void MissHuoBi::on_actionRequest_triggered()
{
// 	RestGetAccountInfo* pRestGetAccountInfo =
// 		m_pImpl->pR->QueryRequest<RestGetAccountInfo>();
// 	if (pRestGetAccountInfo)
// 	{
// 		pRestGetAccountInfo->SendRequest();
// 	}

	RestGetOrders* pRestGetOrders =
			m_pImpl->pR->QueryRequest<RestGetOrders>();
	if (pRestGetOrders)
	{
		pRestGetOrders->SendRequest(CT_BTC);
	}

// 	RestGetNewDealOrders* pRestGetNewDealOrders =
// 		m_pImpl->pR->QueryRequest<RestGetNewDealOrders>();
// 	if (pRestGetNewDealOrders)
// 	{
// 		pRestGetNewDealOrders->SendRequest(CT_BTC);
// 	}
}

void MissHuoBi::slot_ReloadMarketDepth()
{
	ReqMarketDepth* pReqMarketDepth =
		m_pImpl->pM->QueryRequest<ReqMarketDepth>();

	///订阅盘口信息
	pReqMarketDepth->SendRequest(SIT_BTCCNY, HBAPI::PT_PERCENT100);
}

void MissHuoBi::slot_ReloadMarketDepthTop()
{
	ReqMarketDepthTop* pReqMarketDepth =
		m_pImpl->pM->QueryRequest<ReqMarketDepthTop>();

	///订阅盘口信息
	pReqMarketDepth->SendRequest(SIT_BTCCNY);
}

void MissHuoBi::slot_Subscribe()
{
	ReqMsgSubscribe* pReqMsgSubscribe =
		m_pImpl->pM->QueryRequest<ReqMsgSubscribe>();

	MsgTradeDetail* pMsgTradeDetail =
		m_pImpl->pM->QueryMessage<MsgTradeDetail>();

	///订阅盘口信息
	pReqMsgSubscribe->SendRequest(QVector<Subscriber>()
		<< MsgTradeDetail::GetSubscriber(SIT_BTCCNY, PT_PUSHLONG)
		<< MsgMarketDepthTopDiff::GetSubscriber(SIT_BTCCNY, PT_PUSHLONG)
		<< MsgMarketOverview::GetSubscriber(SIT_BTCCNY, PT_PUSHLONG)
		);
}


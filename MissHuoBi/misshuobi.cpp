#include "misshuobi.h"

#include <QDebug>
#include <QVariant>
#include <QJsonObject>
#include <functional>
#include <QTimer>
#include <QHeaderView>
#include <QStateMachine>
#include <QTimer>

#include "common\marketdepthdata.h"
#include "common\marketdepthtopdata.h"
#include "common\misshbdef.h"
#include "hbmarket.h"
#include "hbmarketlinker.h"
#include "hbrest.h"
#include "hbrestlinker.h"
#include "req\reqmsgsubscribe.h"
#include "msg\msgtradedetail.h"
#include "hbapihandle.h"
#include "msg\msgmarketdepthtopdiff.h"
#include "msg\msgmarketoverview.h"
#include "marketdepthmodel.h"
#include "marketboard.h"
#include "controlpanel.h"
#include "autotrade.h"
#include "req\reqkline.h"
#include "msg\msglastkline.h"

#include <QDateTime>
#include "req\reqtimeline.h"

using namespace HBAPI;

class MissHuoBi::Impl
{
public:
	QStateMachine		mConnect;
	QTimer				tmrReconnect;
};


MissHuoBi::MissHuoBi(QWidget *parent)
	: QMainWindow(parent)
	, m_pImpl(new Impl)
{
	ui.setupUi(this);
	Init();
}

typedef void (QTimer::*TS)();

void MissHuoBi::Init()
{
	m_pImpl->tmrReconnect.setInterval(5000);
	m_pImpl->tmrReconnect.setSingleShot(true);

	//////////////////////////////////////////////////////////////////////////
	QState* sWaiting = new QState();
	sWaiting->setObjectName("sWaiting");

	QState* sConnecting = new QState();
	sConnecting->setObjectName("sConnecting");
	QObject::connect(sConnecting, &QState::entered,
		SHBAPI::Instance().GetMarketLinker(), &HbMarketLinker::Connect);

	QState* sRunning = new QState();
	sRunning->setObjectName("sRunning");
	QObject::connect(sRunning, &QState::entered,
		this, &MissHuoBi::slot_Subscribe);

	QState* sBreakOff = new QState();
	sBreakOff->setObjectName("sBreakOff");
	QObject::connect(sBreakOff, &QState::entered,
		&(m_pImpl->tmrReconnect), (TS)&QTimer::start);

	sWaiting->addTransition(ui.actionConnect, &QAction::triggered, sConnecting);
	sConnecting->addTransition(SHBAPI::Instance().GetMarketLinker(),
		&HbMarketLinker::signal_Connected, sRunning);
	sRunning->addTransition(SHBAPI::Instance().GetMarketLinker(),
		&HbMarketLinker::signal_Asystole, sBreakOff);

	sConnecting->addTransition(SHBAPI::Instance().GetMarketLinker(),
		&HbMarketLinker::signal_Disconnected, sWaiting);
	sRunning->addTransition(SHBAPI::Instance().GetMarketLinker(),
		&HbMarketLinker::signal_Disconnected, sWaiting);
	
	sBreakOff->addTransition(&(m_pImpl->tmrReconnect), &QTimer::timeout, sConnecting);

	m_pImpl->mConnect.addState(sWaiting);
	m_pImpl->mConnect.addState(sConnecting);
	m_pImpl->mConnect.addState(sRunning);
	m_pImpl->mConnect.addState(sBreakOff);
	m_pImpl->mConnect.setInitialState(sWaiting);

	m_pImpl->mConnect.start();

	QTimer::singleShot(2500, ui.actionConnect, &QAction::trigger);

	ui.dockLog->hide();

	//////////////////////////////////////////////////////////////////////////
	MarketDepthModel* pMarketDepthModel = ui.wgMarketBoard->GetMarketDepthModel();
	ui.wgControlPanel->GetAutoTrade()->SetPriceTaker(
		std::bind(&MarketDepthModel::GetBuyPrice, pMarketDepthModel, std::placeholders::_1),
		std::bind(&MarketDepthModel::GetSellPrice, pMarketDepthModel, std::placeholders::_1));
}

void MissHuoBi::closeEvent(QCloseEvent * ev)
{
	if (SHBAPI::Instance().GetMarketLinker()->IsConnected())
	{
		QEventLoop loop;
		QObject::connect(SHBAPI::Instance().GetMarketLinker(), 
			&HbMarketLinker::signal_Disconnected, &loop, &QEventLoop::quit);
		QTimer::singleShot(2000, &loop, &QEventLoop::quit);
		SHBAPI::Instance().GetMarketLinker()->Disconnect();
		loop.exec(QEventLoop::ExcludeUserInputEvents);
	}
}

MissHuoBi::~MissHuoBi()
{

}


void MissHuoBi::on_actionRequest_triggered()
{
// 	RestGetAccountInfo* pRestGetAccountInfo =
// 		m_pImpl->pR->QueryRequest<RestGetAccountInfo>();
// 	if (pRestGetAccountInfo)
// 	{
// 		pRestGetAccountInfo->SendRequest();
// 	}

	ReqTimeLine* pReqKLine =
		SHBAPI::Instance().GetMarket()->QueryRequest<ReqTimeLine>();
	if (pReqKLine)
	{
		static int ePeriodType(PT_KLINE1MIN);
		pReqKLine->SendRequest(SIT_BTCCNY, QDateTime::currentDateTime().addSecs(-1800), QDateTime());
	}

// 	RestGetNewDealOrders* pRestGetNewDealOrders =
// 		m_pImpl->pR->QueryRequest<RestGetNewDealOrders>();
// 	if (pRestGetNewDealOrders)
// 	{
// 		pRestGetNewDealOrders->SendRequest(CT_BTC);
// 	}
}


void MissHuoBi::slot_Subscribe()
{
	ReqMsgSubscribe* pReqMsgSubscribe =
		SHBAPI::Instance().GetMarket()->QueryRequest<ReqMsgSubscribe>();

	///订阅盘口信息
	pReqMsgSubscribe->SendRequest(QVector<Subscriber>()
		<< MsgTradeDetail::GetSubscriber(SIT_BTCCNY, PT_PUSHLONG)
		<< MsgMarketDepthTopDiff::GetSubscriber(SIT_BTCCNY, PT_PUSHLONG)
		<< MsgMarketOverview::GetSubscriber(SIT_BTCCNY, PT_PUSHLONG)
		<< MsgLastKLine::GetSubscriber(SIT_BTCCNY, PT_PUSHLONG, QVector<PeriodType>() << PT_KLINE1MIN)
		);

	QTimer::singleShot(1000, ui.wgControlPanel, &ControlPanel::slot_RequestAccountInfo);
}


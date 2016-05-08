#include "autotrade.h"


#include <QStateMachine>
#include <QDebug>

#include "rest\restgetaccountinfo.h"
#include "hbapihandle.h"
#include "hbrest.h"
#include "rest\restbuy.h"
#include "rest\restsell.h"


using namespace HBAPI;

class AutoTrade::Impl
{
public:
	QStateMachine mTrade;
	PriceTaker ptBuy;
	PriceTaker ptSell;
};

AutoTrade::AutoTrade(QObject *parent)
	: QObject(parent)
	, m_pImpl(new Impl)
{
	Init();
}

AutoTrade::~AutoTrade()
{

}

bool AutoTrade::IsRunning()
{
	return m_pImpl->mTrade.isRunning();
}

void AutoTrade::SetRunning(bool bRunning)
{
	bRunning
		? m_pImpl->mTrade.start()
		: m_pImpl->mTrade.stop();
}

void AutoTrade::InitStateMachine()
{
	QStateMachine& mTrade = m_pImpl->mTrade;

	QState* sGetAccountInfo = new QState();
	QObject::connect(sGetAccountInfo, &QState::entered, 
		this, &AutoTrade::slot_GetAccountInfo);

	QState* sWaitChance = new QState();
// 	QObject::connect(sWaitChance, &QState::entered,
// 		this, );

	//////////////////////////////////////////////////////////////////////////

	RestGetAccountInfo* pGetAccountInfo =
		SHBAPI::Instance().GetRest()->QueryRequest<RestGetAccountInfo>();
	sGetAccountInfo->addTransition(pGetAccountInfo, 
		&RestGetAccountInfo::signal_Receive, sWaitChance);

	//////////////////////////////////////////////////////////////////////////
	mTrade.addState(sGetAccountInfo);
	mTrade.addState(sWaitChance);

	mTrade.setInitialState(sGetAccountInfo);
}

void AutoTrade::slot_GetAccountInfo()
{
	RestGetAccountInfo* pGetAccountInfo =
		SHBAPI::Instance().GetRest()->QueryRequest<RestGetAccountInfo>();
	QObject::connect(pGetAccountInfo, &RestGetAccountInfo::signal_Receive,
		this, &AutoTrade::slot_UpdateAccountInfo);

	pGetAccountInfo->SendRequest();
}

void AutoTrade::Init()
{
	RestGetAccountInfo* pGetAccountInfo =
		SHBAPI::Instance().GetRest()->QueryRequest<RestGetAccountInfo>();

	InitStateMachine();
}

void AutoTrade::slot_UpdateAccountInfo(const QSharedPointer<
	AccountInfoData>& ptAccountInfoData)
{

}

void AutoTrade::slot_Buy()
{
	RestBuy* pRestBuy =
		SHBAPI::Instance().GetRest()->QueryRequest<RestBuy>();

	pRestBuy->SendRequest(CT_BTC, (m_pImpl->ptBuy)(3), 0.001);
	qDebug() << (m_pImpl->ptBuy)(3);
}

void AutoTrade::slot_Sell()
{
	RestSell* pRestSell =
		SHBAPI::Instance().GetRest()->QueryRequest<RestSell>();

	pRestSell->SendRequest(CT_BTC, (m_pImpl->ptSell)(3), 0.001);

	qDebug() << (m_pImpl->ptSell)(3);
}

void AutoTrade::slot_StatTradeData(const 
	QSharedPointer<StatTradeData>& ptStatTradeData)
{

}

void AutoTrade::SetPriceTaker(const PriceTaker& ptBuy, const PriceTaker& ptSell)
{
	m_pImpl->ptBuy = ptBuy;
	m_pImpl->ptSell = ptSell;
}

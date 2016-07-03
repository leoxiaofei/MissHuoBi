#include "autotrade.h"


#include <QStateMachine>
#include <QTimer>
#include <QDebug>

#include "rest\restgetaccountinfo.h"
#include "hbapihandle.h"
#include "hbrest.h"
#include "rest\restbuy.h"
#include "rest\restsell.h"
#include "common\traderesult.h"
#include "rest\restorderinfo.h"
#include "rest\restcancelorder.h"


using namespace HBAPI;

namespace
{

class WaitOrderId
{
public:
	int nLastOrderId;	///最近的订单ID
	int nRetry;			///重试次数
};

}

class AutoTrade::Impl
{
public:
	QStateMachine mTrade;
	PriceTaker ptBuy;
	PriceTaker ptSell;

	WaitOrderId wOrderId;

	QSharedPointer<AccountInfoData> ptAccountInfoData;
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

	QState* sJudge = new QState();
	QObject::connect(sJudge, &QState::entered,
		this, &AutoTrade::slot_Judge);

	QState* sWaitBuy = new QState();

	QState* sWaitSell = new QState();


	QState* sBuy = new QState();
	QObject::connect(sBuy, &QState::entered,
		this, &AutoTrade::slot_Buy);

	QState* sSell = new QState();
	QObject::connect(sSell, &QState::entered,
		this, &AutoTrade::slot_Sell);

	QState* sResult = new QState();
	QObject::connect(sResult, &QState::entered,
		this, &AutoTrade::slot_CheckResult);

	QState* sFailure = new QState();
	QObject::connect(sFailure, &QState::entered,
		this, &AutoTrade::slot_CancelOrder);

	sJudge->addTransition(this, &AutoTrade::signal_WaitBuy, sWaitBuy);
	sWaitBuy->addTransition(this, &AutoTrade::signal_Buy, sBuy);
	sBuy->addTransition(this, &AutoTrade::signal_Checkout, sResult);


	sJudge->addTransition(this, &AutoTrade::signal_WaitSell, sWaitSell);
	sWaitSell->addTransition(this, &AutoTrade::signal_Sell, sSell);
	sSell->addTransition(this, &AutoTrade::signal_Checkout, sResult);

	sResult->addTransition(this, &AutoTrade::signal_OrderFinish, sJudge);
	sResult->addTransition(this, &AutoTrade::signal_RetryCountExceeded, sFailure);

	RestCancelOrder* pRestCancelOrder =
		SHBAPI::Instance().GetRest()->QueryRequest<RestCancelOrder>();
	sFailure->addTransition(pRestCancelOrder, &RestCancelOrder::signal_Receive, sJudge);

	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	mTrade.addState(sJudge);
	mTrade.addState(sWaitBuy);
	mTrade.addState(sWaitSell);
	mTrade.addState(sBuy);
	mTrade.addState(sSell);
	mTrade.addState(sResult);
	mTrade.addState(sFailure);
	
	mTrade.setInitialState(sJudge);
}


void AutoTrade::Init()
{
	RestGetAccountInfo* pGetAccountInfo =
		SHBAPI::Instance().GetRest()->QueryRequest<RestGetAccountInfo>();

	QObject::connect(pGetAccountInfo, &RestGetAccountInfo::signal_Receive,
		this, &AutoTrade::slot_UpdateAccountInfo);

	RestSell* pRestSell =
		SHBAPI::Instance().GetRest()->QueryRequest<RestSell>();
	QObject::connect(pRestSell, &RestSell::signal_Receive,
		this, &AutoTrade::slot_TradeResult);

	RestBuy* pRestBuy =
		SHBAPI::Instance().GetRest()->QueryRequest<RestBuy>();
	QObject::connect(pRestBuy, &RestBuy::signal_Receive,
		this, &AutoTrade::slot_TradeResult);

	RestOrderInfo* pRestOrderInfo =
		SHBAPI::Instance().GetRest()->QueryRequest<RestOrderInfo>();
	QObject::connect(pRestOrderInfo, &RestOrderInfo::signal_Receive,
		this, &AutoTrade::slot_OrderInfo);


	InitStateMachine();
}

void AutoTrade::slot_UpdateAccountInfo(const QSharedPointer<
	AccountInfoData>& ptAccountInfoData)
{
	m_pImpl->ptAccountInfoData = ptAccountInfoData;
}

void AutoTrade::slot_Buy()
{
	RestBuy* pRestBuy =
		SHBAPI::Instance().GetRest()->QueryRequest<RestBuy>();

	double dPrice = (m_pImpl->ptBuy)(3);
	double dAmount = m_pImpl->ptAccountInfoData->dAvailableCnyDisplay / dPrice;

	pRestBuy->SendRequest(CT_BTC, (m_pImpl->ptBuy)(3), dAmount);
	qDebug() << dPrice;
}

void AutoTrade::slot_Sell()
{
	RestSell* pRestSell =
		SHBAPI::Instance().GetRest()->QueryRequest<RestSell>();

	pRestSell->SendRequest(CT_BTC, (m_pImpl->ptSell)(3), 
		m_pImpl->ptAccountInfoData->dAvailableBtcDisplay);

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

void AutoTrade::slot_Judge()
{
	if (m_pImpl->ptAccountInfoData->dAvailableBtcDisplay > 0.001)
	{
		///进入卖状态
		void signal_WaitSell();
	}
	else
	{
		///进入买状态
		emit signal_WaitBuy();
	}
}

void AutoTrade::slot_CheckResult()
{
	RestOrderInfo* pRestOrderInfo =
		SHBAPI::Instance().GetRest()->QueryRequest<RestOrderInfo>();

	pRestOrderInfo->SendRequest(CT_BTC, m_pImpl->wOrderId.nLastOrderId);
	++m_pImpl->wOrderId.nRetry;
}

void AutoTrade::slot_TradeResult(const QSharedPointer<HBAPI::TradeResult>& ptTradeResult)
{
	if (ptTradeResult->bResult)
	{
		m_pImpl->wOrderId.nLastOrderId = ptTradeResult->uOrderId;
		m_pImpl->wOrderId.nRetry = -1;

		emit signal_Checkout();
	}
	else
	{
		/// 报错

	}
}

void AutoTrade::slot_OrderInfo(const QSharedPointer<HBAPI::OrderInfo>& ptOrderInfo)
{
	if (ptOrderInfo->nId == m_pImpl->wOrderId.nLastOrderId)
	{
		if (ptOrderInfo->eStatus != OS_COMPLETED)
		{
			if (m_pImpl->wOrderId.nRetry < 9)
			{
				///半秒后请求下一次
				QTimer::singleShot(500, this, &AutoTrade::slot_CheckResult);
			}
			else
			{
				///超出重试次数
				emit signal_RetryCountExceeded();
			}
		}
		else
		{
			///如果完成，那么恢复到最开始状态
			emit signal_OrderFinish();
		}
	}
	else
	{
		/// 报错
	}
}

void AutoTrade::slot_CancelOrder()
{
	///重试超过次数，取消订单
	RestCancelOrder* pRestCancelOrder =
		SHBAPI::Instance().GetRest()->QueryRequest<RestCancelOrder>();

	pRestCancelOrder->SendRequest(CT_BTC, m_pImpl->wOrderId.nLastOrderId);

}

#include "controlpanel.h"

#include <QStateMachine>
#include <QMenu>

#include "autotrade.h"
#include "rest\restgetaccountinfo.h"
#include "hbrest.h"
#include "hbapihandle.h"
#include "ordersmodel.h"
#include "rest\restgetorders.h"
#include "rest\restcancelorder.h"

using namespace HBAPI;

class ControlPanel::Impl
{
public:
	QStateMachine mUI;
	AutoTrade*	  autoTrade;
	OrdersModel*  mdOrders;
};

ControlPanel::ControlPanel(QWidget *parent)
: QWidget(parent)
, m_pImpl(new Impl)
{
	ui.setupUi(this);
	Init();
}

ControlPanel::~ControlPanel()
{

}

AutoTrade* ControlPanel::GetAutoTrade() const
{
	return m_pImpl->autoTrade;
}

void ControlPanel::Init()
{
	m_pImpl->mdOrders = new OrdersModel(this);
	ui.tvOrders->setModel(m_pImpl->mdOrders);

	RestGetOrders* pRestGetOrders =
		SHBAPI::Instance().GetRest()->QueryRequest<RestGetOrders>();
	QObject::connect(pRestGetOrders, &RestGetOrders::signal_Receive,
		this, &ControlPanel::slot_UpdateOrdersData);

	RestCancelOrder* pRestCancelOrder =
		SHBAPI::Instance().GetRest()->QueryRequest<RestCancelOrder>();
	QObject::connect(pRestCancelOrder, &RestCancelOrder::signal_Receive,
		this, &ControlPanel::slot_RequestAccountInfo);

	m_pImpl->autoTrade = new AutoTrade(this);

	RestGetAccountInfo* pGetAccountInfo =
		SHBAPI::Instance().GetRest()->QueryRequest<RestGetAccountInfo>();
	QObject::connect(pGetAccountInfo, &RestGetAccountInfo::signal_Receive, 
		this, &ControlPanel::slot_UpdateAccountInfo);

	QObject::connect(ui.btnBuy, &QPushButton::clicked,
		m_pImpl->autoTrade, &AutoTrade::slot_Buy);
	QObject::connect(ui.btnSell, &QPushButton::clicked,
		m_pImpl->autoTrade, &AutoTrade::slot_Sell);

	InitStateMachine();
}


void ControlPanel::InitStateMachine()
{
	AutoTrade* pAutoTrade = m_pImpl->autoTrade;

	QState* pWaiting = new QState();
	pWaiting->assignProperty(ui.btnStop, "visible", false);
	pWaiting->assignProperty(ui.btnStart, "visible", true);
	pWaiting->assignProperty(pAutoTrade, "running", false);

	QState* pRunning = new QState();
	pRunning->assignProperty(ui.btnStart, "visible", false);
	pRunning->assignProperty(ui.btnStop, "visible", true);
	pRunning->assignProperty(pAutoTrade, "running", true);

	pWaiting->addTransition(ui.btnStart, SIGNAL(clicked()), pRunning);
	pRunning->addTransition(ui.btnStop, SIGNAL(clicked()), pWaiting);

	QStateMachine& mUI = m_pImpl->mUI;
	mUI.addState(pWaiting);
	mUI.addState(pRunning);
	mUI.setInitialState(pWaiting);

	mUI.start();
}

void ControlPanel::slot_UpdateAccountInfo(const
	QSharedPointer<HBAPI::AccountInfoData>& ptAccountInfoData)
{
	ui.lblRMB->setText(QString::number(ptAccountInfoData->dAvailableCnyDisplay, 'f', 2));
	ui.lblBitcoin->setText(QString::number(ptAccountInfoData->dAvailableBtcDisplay, 'f', 4));
}

void ControlPanel::slot_UpdateOrdersData(const QList<HBAPI::OrdersData>& listOrdersData)
{
	m_pImpl->mdOrders->SetDataSrc(listOrdersData);
}

void ControlPanel::slot_OrdersMenuRequested(const QPoint& pos)
{
	QModelIndex index = ui.tvOrders->indexAt(pos);
	if (index.isValid())
	{
		QMenu menu;
		menu.addAction(QStringLiteral("È¡Ïû¶©µ¥"), this, &ControlPanel::slot_ActCancelOrder);
		menu.exec(ui.tvOrders->viewport()->mapToGlobal(pos));
	}
}

void ControlPanel::slot_ActCancelOrder()
{
	QModelIndex index = ui.tvOrders->currentIndex();
	if (index.isValid())
	{
		int nOrderId = m_pImpl->mdOrders->GetOrderId(index);
		RestCancelOrder* pRestCancelOrder =
			SHBAPI::Instance().GetRest()->QueryRequest<RestCancelOrder>();

		pRestCancelOrder->SendRequest(CT_BTC, nOrderId);
	}
}

void ControlPanel::slot_RequestAccountInfo()
{
	RestGetAccountInfo* pGetAccountInfo =
		SHBAPI::Instance().GetRest()->QueryRequest<RestGetAccountInfo>();
	pGetAccountInfo->SendRequest();

	RestGetOrders* pRestGetOrders =
		SHBAPI::Instance().GetRest()->QueryRequest<RestGetOrders>();
	pRestGetOrders->SendRequest(CT_BTC);
}

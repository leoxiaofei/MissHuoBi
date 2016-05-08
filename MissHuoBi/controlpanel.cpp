#include "controlpanel.h"

#include <QStateMachine>

#include "autotrade.h"
#include "rest\restgetaccountinfo.h"
#include "hbrest.h"
#include "hbapihandle.h"

using namespace HBAPI;

class ControlPanel::Impl
{
public:
	QStateMachine mUI;
	AutoTrade*	  autoTrade;

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

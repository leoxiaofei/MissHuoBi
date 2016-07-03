#include "panelboard.h"
#include "msg\msgmarketoverview.h"
#include "hbapihandle.h"

#include <QWidget>
#include <QDateTime>
#include "hbmarket.h"

using namespace HBAPI;

PanelBoard::PanelBoard(QWidget* parent)
: QWidget(parent)
{
	ui.setupUi(this);
	Init();
}

PanelBoard::~PanelBoard()
{

}

void PanelBoard::slot_UpadePanel(const QSharedPointer<MarketOverviewData>& ptMarketOverviewData)
{
	static QString strDtFmt = "yyyy-MM-dd HH:mm:ss";
	static QString strRMB = QString::fromUtf8("\357\277\245 ");
	static QString strBC = QString::fromUtf8("\340\270\277 ");
	ui.lblPriceNew->setText(strRMB + QString::number(ptMarketOverviewData->dPriceNew, 'f', 2));
	ui.lblUpdateTime->setText(QDateTime::currentDateTime().toString(strDtFmt));
	ui.lblPriceHigh->setText(QString::number(ptMarketOverviewData->dPriceHigh, 'f', 2));
	ui.lblPriceLow->setText(QString::number(ptMarketOverviewData->dPriceLow, 'f', 2));
	ui.lblUpdownRatio->setText(QString::number((ptMarketOverviewData->dPriceNew -
		ptMarketOverviewData->dPriceOpen) / ptMarketOverviewData->dPriceOpen * 100, 'f', 2) + "%");
	ui.lblAmount->setText(strBC + QString::number(ptMarketOverviewData->dTotalAmount, 'f', 4));
}

QSize PanelBoard::sizeHint() const
{
	return QSize(250, 135);
}

void PanelBoard::Init()
{
	MsgMarketOverview* pMsgMarketDetail =
		SHBAPI::Instance().GetMarket()->QueryMessage<MsgMarketOverview>();

	QObject::connect(pMsgMarketDetail, &MsgMarketOverview::signal_Receive,
		this, &PanelBoard::slot_UpadePanel);
}


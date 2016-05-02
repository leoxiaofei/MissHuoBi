#include "panelboard.h"
#include "msg\msgmarketoverview.h"

#include <QWidget>
#include <QDateTime>

PanelBoard::PanelBoard(QWidget* parent)
: QWidget(parent)
{
	ui.setupUi(this);
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


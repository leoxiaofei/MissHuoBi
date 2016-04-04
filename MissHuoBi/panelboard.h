#ifndef __PANELBOARD_H__
#define __PANELBOARD_H__

#include "ui_panelboard.h"

namespace HBAPI
{
	class MarketOverviewData;
}

using HBAPI::MarketOverviewData;

class PanelBoard : public QWidget
{
	Q_OBJECT
public:
	PanelBoard(QWidget* parent = 0);
	~PanelBoard();

public slots:
	void slot_UpadePanel(const QSharedPointer<MarketOverviewData>& ptMarketOverviewData);

private:
	Ui::PanelBoard ui;
};


#endif // __PANELBOARD_H__
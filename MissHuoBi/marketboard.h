#ifndef MARKETBOARD_H
#define MARKETBOARD_H

#include <QWidget>
#include "ui_marketboard.h"

class MarketDepthModel;

class MarketBoard : public QWidget
{
	Q_OBJECT

public:
	MarketBoard(QWidget *parent = 0);
	~MarketBoard();

	void Init(MarketDepthModel* pMarketDepthModel);

private:
	Ui::MarketBoard ui;
	class Impl;
	QScopedPointer<Impl> m_pImpl;
};

#endif // MARKETBOARD_H

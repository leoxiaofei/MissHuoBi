#ifndef TRADEBOARD_H
#define TRADEBOARD_H

#include <QWidget>
#include "ui_tradeboard.h"

class TradeBoard : public QWidget
{
	Q_OBJECT

public:
	TradeBoard(QWidget *parent = 0);
	~TradeBoard();

	void Init();

private:
	Ui::TradeBoard ui;
};

#endif // TRADEBOARD_H

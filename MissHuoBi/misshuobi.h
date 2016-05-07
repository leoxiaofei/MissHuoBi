#ifndef MISSHUOBI_H
#define MISSHUOBI_H


#include <QtWidgets/QMainWindow>
#include "ui_misshuobi.h"

class MissHuoBi : public QMainWindow
{
	Q_OBJECT

public:
	MissHuoBi(QWidget *parent = 0);
	~MissHuoBi();

public Q_SLOTS:
	void on_actionConnect_triggered();
	void on_actionDisconnect_triggered();
	void on_actionRequest_triggered();
	void slot_ReloadMarketDepth();
	void slot_ReloadMarketDepthTop();

protected Q_SLOTS:
	void slot_Subscribe();


protected:
	void Init();

	virtual void closeEvent(QCloseEvent * ev) override;

private:
	Ui::MissHuoBiClass ui;
	class Impl;
	QScopedPointer<Impl> m_pImpl;
};

#endif // MISSHUOBI_H

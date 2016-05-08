#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include "ui_controlpanel.h"


namespace HBAPI
{
	class AccountInfoData;
}

class AutoTrade;

class ControlPanel : public QWidget
{
	Q_OBJECT

public:
	ControlPanel(QWidget *parent = 0);
	~ControlPanel();

	void Init();

	AutoTrade* GetAutoTrade() const;

public slots:
	void slot_UpdateAccountInfo(const 
		QSharedPointer<HBAPI::AccountInfoData>& ptAccountInfoData);

protected:
	void InitStateMachine();

private:
	Ui::ControlPanel ui;
	class Impl;
	QScopedPointer<Impl> m_pImpl;
};

#endif // CONTROLPANEL_H

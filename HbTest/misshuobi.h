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
	

protected Q_SLOTS:
	void on_sioClient_heartbeatReceived();
	void on_sioClient_messageReceived(const QString& message);
	void on_sioClient_errorReceived(const QString& reason, const QString& advice);
	void on_sioClient_connected(const QString& endpoint);
	void on_sioClient_disconnected(const QString& endpoint);

protected:

private:
	Ui::MissHuoBiClass ui;
	class Impl;
	QScopedPointer<Impl> m_pImpl;
};

#endif // MISSHUOBI_H

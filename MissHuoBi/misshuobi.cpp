#include "misshuobi.h"

#include <QWebSocket>
#include <QDebug>
#include <QUrl>
#include <QVariant>
#include <QJsonObject>
#include <functional>
#include <QSocketIoClient>

#include "hbapi\request\requestparser.h"

using namespace HBAPI;

class MissHuoBi::Impl
{
public:
	QSocketIoClient* pIO;
	RequestParser*   pRP;
};


MissHuoBi::MissHuoBi(QWidget *parent)
	: QMainWindow(parent)
	, m_pImpl(new Impl)
{
	m_pImpl->pIO = new QSocketIoClient(this);
	m_pImpl->pIO->setObjectName("sioClient");

	m_pImpl->pRP = new RequestParser(this);
	m_pImpl->pRP->InitParser(m_pImpl->pIO);

	m_pImpl->pIO->on("message", [=](const QJsonArray& returnValue){
		qDebug() << "message:" << returnValue; });

// 	m_pIO->on("connect", [=](const QJsonArray& returnValue){
// 		qDebug() << "connect."; });
// 
// 	m_pIO->on("disconnect", [=](const QJsonArray& returnValue){
// 		qDebug() << "disconnect."; });

	ui.setupUi(this);
}

MissHuoBi::~MissHuoBi()
{

}

void MissHuoBi::on_actionConnect_triggered()
{
	qDebug() << "on_actionConnect_triggered";

	QString strUrl = "ws://hq.huobi.com:80";
	m_pImpl->pIO->open(QUrl(strUrl));

}

void MissHuoBi::on_actionDisconnect_triggered()
{
	qDebug() << "on_actionDisconnect_triggered";
	m_pImpl->pIO->close();
}

void MissHuoBi::on_actionRequest_triggered()
{
	//QString strMsg = '{"symbolId":"btccny","version":1,"msgType":"reqMarketDepthTop","requestIndex":1405131204513}';
	m_pImpl->pIO->emitMessage("request", QJsonObject(
	{ { "symbolId", "btccny" }, { "version", "1" }, { "msgType", "reqMarketDepthTop" }, { "requestIndex", "1405131204513" } }
	).toVariantMap());
}

void MissHuoBi::on_sioClient_heartbeatReceived()
{
	qDebug() << "Received heartbeat";
}

void MissHuoBi::on_sioClient_messageReceived(const QString& message)
{
	qDebug() << "on_sioClient_messageReceived:" << message;
}

void MissHuoBi::on_sioClient_errorReceived(const QString& reason, const QString& advice)
{
	qDebug() << "on_sioClient_errorReceived:" << reason << advice;
}

void MissHuoBi::on_sioClient_connected(const QString& endpoint)
{
	qDebug() << "on_sioClient_connected:" << endpoint;
}

void MissHuoBi::on_sioClient_disconnected(const QString& endpoint)
{
	qDebug() << "on_sioClient_disconnected:" << endpoint;
}


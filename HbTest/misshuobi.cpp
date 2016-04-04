#include "misshuobi.h"

#include <QWebSocket>
#include <QDebug>
#include <QUrl>
#include <QVariant>
#include <QJsonObject>
#include <functional>
#include <QSocketIoClient>

#include "hbparser.h"
#include "req\reqmsgsubscribe.h"
#include "msg\msgmarketdepthdiff.h"
#include "common\misshbdef.h"

using namespace HBAPI;

class MissHuoBi::Impl
{
public:
	QSocketIoClient* pIO;
	HbParser*   pRP;
};

typedef void (QSocketIoClient::*FEM)(const QString &, const QVariantMap &);
typedef std::function<void(const QJsonArray&)> Fp;

MissHuoBi::MissHuoBi(QWidget *parent)
	: QMainWindow(parent)
	, m_pImpl(new Impl)
{
	m_pImpl->pIO = new QSocketIoClient(this);
	m_pImpl->pIO->setObjectName("sioClient");

	m_pImpl->pRP = new HbParser(this);

	m_pImpl->pRP->InitParser(std::bind((FEM)&QSocketIoClient::emitMessage, m_pImpl->pIO, std::placeholders::_1, std::placeholders::_2));

	m_pImpl->pIO->on("request", (Fp)std::bind(&HbParser::ParserRequest, m_pImpl->pRP, std::placeholders::_1));
	m_pImpl->pIO->on("message", (Fp)std::bind(&HbParser::ParserMessage, m_pImpl->pRP, std::placeholders::_1));

// 	m_pImpl->pIO->on("message", [=](const QJsonArray& returnValue){
// 		qDebug() << "message:" << returnValue; });

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
// 	m_pImpl->pIO->emitMessage("request", QJsonObject(
// 	{ { "symbolId", "btccny" }, { "version", "1" }, { "msgType", "reqMarketDepthTop" }, { "requestIndex", "1405131204513" } }
// 	).toVariantMap());

// 	ReqMarketDepthTop* pReqMarketDepthTop =
// 		m_pImpl->pRP->QueryRequest<ReqMarketDepthTop>();
// 	pReqMarketDepthTop->SendRequest("btccny");

	ReqMsgSubscribe* pReqMsgSubscribe =
		m_pImpl->pRP->QueryRequest<ReqMsgSubscribe>();

	pReqMsgSubscribe->SendRequest(QVector<Subscriber>()
		<< MsgMarketDepthDiff::GetSubscriber(SIT_BTCCNY, PT_PUSHLONG, QVector<PercentType>() << PT_PERCENT50));
// 	MsgTradeDetail a;
// 	MsgMarketDetail b;
// 	pReqMsgSubscribe->SendRequest(QVector<Subscriber>() << a.GetSubscriber(SIT_BTCCNY, PT_PUSHSHORT)
// 		<< b.GetSubscriber(SIT_BTCCNY, PT_PUSHLONG));
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


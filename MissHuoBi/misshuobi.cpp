﻿#include "misshuobi.h"

#include <QWebSocket>
#include <QDebug>
#include <QUrl>
#include <QVariant>
#include <QJsonObject>
#include <functional>
#include <QSocketIoClient>
#include <QTimer>

#include "panelboard.h"
#include "hbparser.h"
#include "req\reqmsgsubscribe.h"
#include "common\misshbdef.h"
#include "msg\msgmarketoverview.h"

using namespace HBAPI;

class MissHuoBi::Impl
{
public:
	QSocketIoClient* pIO;
	HbParser*   pRP;
};

typedef void (QSocketIoClient::*Fem)(const QString &, const QVariantMap &);
typedef std::function<void(const QJsonArray&)> Fp;

MissHuoBi::MissHuoBi(QWidget *parent)
	: QMainWindow(parent)
	, m_pImpl(new Impl)
{
	m_pImpl->pIO = new QSocketIoClient(this);
	m_pImpl->pIO->setObjectName("sioClient");
	ui.setupUi(this);
	Init();
}

void MissHuoBi::Init()
{
	m_pImpl->pRP = new HbParser(this);
	m_pImpl->pRP->InitParser(std::bind((Fem)&QSocketIoClient::emitMessage, m_pImpl->pIO, std::placeholders::_1, std::placeholders::_2));

	m_pImpl->pIO->on("request", (Fp)std::bind(&HbParser::ParserRequest, m_pImpl->pRP, std::placeholders::_1));
	m_pImpl->pIO->on("message", (Fp)std::bind(&HbParser::ParserMessage, m_pImpl->pRP, std::placeholders::_1));

	MsgMarketOverview* pMsgMarketDetail =
		m_pImpl->pRP->QueryMessage<MsgMarketOverview>();

	QObject::connect(pMsgMarketDetail, &MsgMarketOverview::signal_Receive, ui.wgPanelBoard, &PanelBoard::slot_UpadePanel);

	QTimer::singleShot(1000, this, &MissHuoBi::on_actionConnect_triggered);
}

void MissHuoBi::Subscribe()
{
	ReqMsgSubscribe* pReqMsgSubscribe =
		m_pImpl->pRP->QueryRequest<ReqMsgSubscribe>();

	///订阅盘口信息
	pReqMsgSubscribe->SendRequest(QVector<Subscriber>()
		<< MsgMarketOverview::GetSubscriber(SIT_BTCCNY, PT_PUSHSHORT));
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
	Subscribe();
}

void MissHuoBi::on_sioClient_disconnected(const QString& endpoint)
{
	qDebug() << "on_sioClient_disconnected:" << endpoint;
}


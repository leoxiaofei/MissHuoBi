#include "hbmarketlinker.h"

#include <QSocketIoClient>
#include <QTimer>

namespace HBAPI
{
	typedef void (QSocketIoClient::*Fem)(const QString &, const QVariantMap &);

	class HbMarketLinker::Impl
	{
	public:
		QSocketIoClient*	sioClient;
		QTimer				tmrAsystole;
		QUrl				url;
		bool				bConnected;

		void Init(HbMarketLinker* parent);
	};

	void HbMarketLinker::Impl::Init(HbMarketLinker* parent)
	{
		sioClient = new QSocketIoClient(parent);
		sioClient->setObjectName("sioClient");

		tmrAsystole.setInterval(70000);
		tmrAsystole.setSingleShot(true);

		QObject::connect(&tmrAsystole, &QTimer::timeout, parent, &HbMarketLinker::signal_Asystole);

		QMetaObject::connectSlotsByName(parent);
	}

	HbMarketLinker::HbMarketLinker(QObject* parent /*= 0*/)
		: QObject(parent)
		, m_pImpl(new Impl)
	{
		m_pImpl->Init(this);
	}

	HbMarketLinker::~HbMarketLinker()
	{

	}

	void HbMarketLinker::SetUrl(const QUrl& url)
	{
		m_pImpl->url = url;
	}

	void HbMarketLinker::SetRecvFunc(const FuncRecvMarket& fpRequest, const FuncRecvMarket& fpMessage)
	{
		m_pImpl->sioClient->on("request", fpRequest);
		m_pImpl->sioClient->on("message", fpMessage);
	}

	void HbMarketLinker::Connect()
	{
		m_pImpl->sioClient->open(m_pImpl->url);
		m_pImpl->tmrAsystole.start();
	}

	void HbMarketLinker::Disconnect()
	{
		m_pImpl->sioClient->close();
	}

	HBAPI::FuncEmitMarket HbMarketLinker::GetSendFunc() const
	{
		return std::bind((Fem)&QSocketIoClient::emitMessage, 
			m_pImpl->sioClient, std::placeholders::_1, std::placeholders::_2);
	}

	bool HbMarketLinker::IsConnected() const
	{
		return m_pImpl->bConnected;
	}

	void HbMarketLinker::on_sioClient_heartbeatReceived()
	{
		m_pImpl->tmrAsystole.start();
		static QDateTime dt = QDateTime::currentDateTime();
		qDebug() << "Received heartbeat:" << QDateTime::currentDateTime().secsTo(dt);
	}

	void HbMarketLinker::on_sioClient_messageReceived(const QString& message)
	{
		qDebug() << "on_sioClient_messageReceived:" << message;
	}

	void HbMarketLinker::on_sioClient_errorReceived(const QString& reason, const QString& advice)
	{
		emit signal_Asystole();
		qDebug() << "on_sioClient_errorReceived:" << reason << advice;
	}

	void HbMarketLinker::on_sioClient_connected(const QString& endpoint)
	{
		m_pImpl->bConnected = true;
		emit signal_Connected();
		qDebug() << "on_sioClient_connected:" << endpoint;
	}

	void HbMarketLinker::on_sioClient_disconnected(const QString& endpoint)
	{
		m_pImpl->bConnected = false;
		emit signal_Disconnected();
		qDebug() << "on_sioClient_disconnected:" << endpoint;
	}

}

#include "hbmarketlinker.h"

#include <QSocketIoClient>


namespace HBAPI
{
	typedef void (QSocketIoClient::*Fem)(const QString &, const QVariantMap &);

	class HbMarketLinker::Impl
	{
	public:
		QSocketIoClient* sioClient;
		QUrl url;

		void Init(QObject* parent);
	};

	void HbMarketLinker::Impl::Init(QObject* parent)
	{
		sioClient = new QSocketIoClient(parent);
		sioClient->setObjectName("sioClient");

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

	void HbMarketLinker::on_sioClient_heartbeatReceived()
	{
		qDebug() << "Received heartbeat";
	}

	void HbMarketLinker::on_sioClient_messageReceived(const QString& message)
	{
		qDebug() << "on_sioClient_messageReceived:" << message;
	}

	void HbMarketLinker::on_sioClient_errorReceived(const QString& reason, const QString& advice)
	{
		qDebug() << "on_sioClient_errorReceived:" << reason << advice;
	}

	void HbMarketLinker::on_sioClient_connected(const QString& endpoint)
	{
		emit signal_Connected();
		qDebug() << "on_sioClient_connected:" << endpoint;
	}

	void HbMarketLinker::on_sioClient_disconnected(const QString& endpoint)
	{
		emit signal_Disconnected();
		qDebug() << "on_sioClient_disconnected:" << endpoint;
	}

}

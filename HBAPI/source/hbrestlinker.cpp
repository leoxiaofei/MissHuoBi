#include "hbrestlinker.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslConfiguration>

namespace HBAPI
{

	class HbRestLinker::Impl
	{
	public:
		QNetworkAccessManager manager;
		QNetworkRequest	request;

		FuncRecvRest funcRecvRest;
	};

	HbRestLinker::HbRestLinker(QObject* parent /*= 0*/)
		: QObject(parent)
		, m_pImpl(new Impl)
	{
		Init();
	}

	HbRestLinker::~HbRestLinker()
	{

	}

	void HbRestLinker::SetUrl(const QUrl& url)
	{
		m_pImpl->request.setUrl(url);
	}

	void HbRestLinker::Init()
	{
		QObject::connect(&m_pImpl->manager, &QNetworkAccessManager::finished,
			this, &HbRestLinker::slot_ReceiveData);

		m_pImpl->request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

		QSslConfiguration config;
		config.setPeerVerifyMode(QSslSocket::VerifyNone);
		config.setProtocol(QSsl::AnyProtocol);
		
		m_pImpl->request.setSslConfiguration(config);
	}

	long HbRestLinker::PostData(const QByteArray& ba)
	{
		QNetworkReply * reply = m_pImpl->manager.post(m_pImpl->request, ba);
		return reinterpret_cast<long>(reply);
	}

	void HbRestLinker::slot_ReceiveData(QNetworkReply *reply)
	{
		m_pImpl->funcRecvRest(reinterpret_cast<long>(reply), reply->readAll());
	}

	void HbRestLinker::SetRecvFunc(const FuncRecvRest& funcRecvRest)
	{
		m_pImpl->funcRecvRest = funcRecvRest;
	}

}
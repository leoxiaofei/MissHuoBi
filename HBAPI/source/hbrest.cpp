#include "hbrest.h"
#include "rest\restrequestbase.h"
#include "common\mapkv.h"

#include <QDateTime>
#include <QSharedPointer>
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include "rest\restgetaccountinfo.h"

namespace HBAPI
{
	typedef QHash<QLatin1String, QSharedPointer<RestRequestBase> >   HsRequest;

	class HbRest::Impl
	{
	public:
		HsRequest hsRequest;
		QString strAccessKey;
		QString strSecretKey;

		FuncEmitRest funcEmitRest;
		QMap<long, RestRequestBase*> mapResponse;
	};

	HbRest::HbRest(QObject* parent /*= 0*/)
	: QObject(parent)
	, m_pImpl(new Impl)
	{

	}

	HbRest::~HbRest()
	{

	}

	void HbRest::Packer(MapKV& mapParams, MapKV& mapExtra, RestRequestBase* pBase)
	{
		mapParams.insert(szRestKName[RK_METHOD], pBase->GetRestType());
		mapParams.insert(szRestKName[RK_ACCESS_KEY], m_pImpl->strAccessKey);
		mapParams.insert(szRestKName[RK_CREATED], QDateTime::currentDateTime().toTime_t());
		mapParams.insert(szRestKName[RK_SIGN], CreateSign(mapParams));
		
		mapParams += mapExtra;

		long nRequestId = m_pImpl->funcEmitRest(mapParams.toUrlEncode());
		m_pImpl->mapResponse[nRequestId] = pBase;
	}

	void HbRest::RegRequestBase(const char* sz, RestRequestBase* pBase)
	{
		pBase->SetSendFunc(std::bind(&HbRest::Packer, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		m_pImpl->hsRequest[QLatin1String(sz)] = QSharedPointer<RestRequestBase>(pBase);
	}

	RestRequestBase* HbRest::QueryRequestBase(const char* sz) const
	{
		return m_pImpl->hsRequest.value(QLatin1String(sz)).data();
	}

	QString HbRest::CreateSign(MapKV& mapParams)
	{
		QString strRet;

		mapParams.insert(szRestKName[RK_SECRET_KEY], m_pImpl->strSecretKey);
		mapParams.sort();
		
		strRet = QCryptographicHash::hash(mapParams.toUrlEncode(), QCryptographicHash::Md5).toHex();
		mapParams.remove(szRestKName[RK_SECRET_KEY]);
		return strRet;
	}

	void HbRest::ParserRequest(long nRequestId, const QByteArray& ba)
	{
		if (RestRequestBase* pBase = m_pImpl->mapResponse.take(nRequestId))
		{
			QJsonDocument jd = QJsonDocument::fromJson(ba);
			pBase->ReceiveJson(jd.object());

		}
	}

	void HbRest::SetKey(const QString& strAccessKey, const QString& strSecretKey)
	{
		m_pImpl->strAccessKey = strAccessKey;
		m_pImpl->strSecretKey = strSecretKey;
	}

	void HbRest::InitParser(const FuncEmitRest& emitRest)
	{
		m_pImpl->funcEmitRest = emitRest;

		RegRequest<RestGetAccountInfo>();

	}

}

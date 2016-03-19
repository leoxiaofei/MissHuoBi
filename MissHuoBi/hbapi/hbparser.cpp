#include "hbparser.h"
#include <QtSocketIo>
#include <QMap>
#include <QJsonObject>
#include <QLatin1String>

#include "requestbase.h"
#include "reqmarketdepthtop.h"
#include "idCreater.hpp"
#include "reqmsgsubscribe.h"
#include "subscribebase.h"
#include "msgtradedetail.h"



namespace HBAPI
{
	typedef std::function<void(const QJsonArray&)> Fp;
	typedef QHash<QLatin1String, QSharedPointer<RequestBase> >   HsRequest;
	typedef QHash<QLatin1String, QSharedPointer<SubscribeBase> > HsMessage;

class HbParser::Impl
{
public:
	QSocketIoClient* pIO;

	IdCreater<int> icRequestIndex;

	HsRequest hsRequest;
	HsMessage hsMessage;

};

HbParser::HbParser(QObject* parent)
: QObject(parent)
, m_pImpl(new Impl)
{
	
}

HbParser::~HbParser()
{

}

void HbParser::InitParser(QSocketIoClient* pIO)
{
	Fp fpReq = std::bind(&HbParser::ParserRequest, this, std::placeholders::_1);
	pIO->on("request", fpReq);

	Fp fpMsg = std::bind(&HbParser::ParserMessage, this, std::placeholders::_1);
	pIO->on("message", fpMsg);

	m_pImpl->pIO = pIO;

	//////////////////////////////////////////////////////////////////////////

	RegRequest<ReqMarketDepthTop>();
	RegRequest<ReqMsgSubscribe>();
	RegMessage<MsgTradeDetail>();
}

void HbParser::ParserRequest(const QJsonArray& returnValue)
{
	for (QJsonArray::const_iterator citor = returnValue.constBegin();
		citor != returnValue.constEnd(); ++citor)
	{
		if (citor->isObject())
		{
			QJsonObject json = citor->toObject();
			
			do 
			{
				///°æ±¾ÅÐ¶Ï
				if (json[szAttributeName[AN_VERSION]].toInt() != PV_CURRENT)
				{
					break;
				}

				qDebug() << json[szAttributeName[AN_REQUESTINDEX]].toInt();

				if (json[szAttributeName[AN_RETCODE]].toInt() != CODE_OK)
				{
					qDebug() << "ErrorCode:" << json[szAttributeName[AN_RETCODE]];
					break;
				}

				QByteArray baMsgType = json[szAttributeName[AN_MSGTYPE]].toString().toLatin1();
				HsRequest::const_iterator ciFind = 
					m_pImpl->hsRequest.constFind(QLatin1String(baMsgType.data(), baMsgType.size()));
				if (ciFind == m_pImpl->hsRequest.constEnd())
				{
					break;
				}

				(*ciFind)->ReceiveJson(json);

			} while (0);

		}
	}
}

void HbParser::RegRequestBase(const char* sz, RequestBase* pBase)
{
	pBase->SetSendFunc(std::bind(&HbParser::Packer, this, std::placeholders::_1));
	m_pImpl->hsRequest[QLatin1String(sz)] = QSharedPointer<RequestBase>(pBase);
}

template<class T>
void HbParser::PrintJson(const T& json)
{
	for (T::const_iterator citorjson = json.constBegin();
		citorjson != json.constEnd(); ++citorjson)
	{
		qDebug() << citorjson.key() << ":" << citorjson.value();
	}
}

int HbParser::Packer(QJsonObject& json)
{
	int nRet = m_pImpl->icRequestIndex();

	json.insert(szAttributeName[AN_VERSION], PV_CURRENT);
	json.insert(szAttributeName[AN_REQUESTINDEX], nRet);

	m_pImpl->pIO->emitMessage(szAttributeName[AN_REQUEST], json.toVariantMap());

	return nRet;
}

RequestBase* HbParser::QueryRequestBase(const char* sz) const
{
	return m_pImpl->hsRequest.value(QLatin1String(sz)).data();
}

void HbParser::ParserMessage(const QJsonArray& returnValue)
{
	for (QJsonArray::const_iterator citor = returnValue.constBegin();
		citor != returnValue.constEnd(); ++citor)
	{
		if (citor->isObject())
		{
			QJsonObject json = citor->toObject();

			do
			{
				///°æ±¾ÅÐ¶Ï
				if (json[szAttributeName[AN_VERSION]].toInt() != PV_CURRENT)
				{
					break;
				}

 				qDebug() << json[szAttributeName[AN__ID]].toInt();

				QByteArray baMsgType = json[szAttributeName[AN_MSGTYPE]].toString().toLatin1();
				HsMessage::const_iterator ciFind =
					m_pImpl->hsMessage.constFind(QLatin1String(baMsgType.data(), baMsgType.size()));
				if (ciFind == m_pImpl->hsMessage.constEnd())
				{
					break;
				}

				(*ciFind)->ReceiveJson(json[szAttributeName[AN_PAYLOAD]].toObject());

			} while (0);

		}
	}
}

void HbParser::RegMessageBase(const char* sz, SubscribeBase* pBase)
{
	m_pImpl->hsMessage[QLatin1String(sz)] = QSharedPointer<SubscribeBase>(pBase);

}

SubscribeBase* HbParser::QueryMessageBase(const char* sz) const
{
	return m_pImpl->hsMessage.value(QLatin1String(sz)).data();
}

}

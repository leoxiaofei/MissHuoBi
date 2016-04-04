#include "hbparser.h"

#include <QMap>
#include <QJsonObject>
#include <QLatin1String>
#include <QDebug>

#include "req/requestbase.h"
#include "req/reqmarketdepthtop.h"
#include "tools/idCreater.hpp"
#include "req/reqmsgsubscribe.h"
#include "req/reqmsgunsubscribe.h"
#include "msg/subscribebase.h"
#include "msg/msgtradedetail.h"
#include "msg/msgmarketdetail.h"
#include "msg/msglastkLine.h"
#include "msg/msglasttimeline.h"
#include "msg/msgmarketdepthdiff.h"
#include "msg/msgmarketdepthtopdiff.h"
#include "msg/msgmarketoverview.h"
#include "msg/msgmarketstatic.h"



namespace HBAPI
{
	typedef QHash<QLatin1String, QSharedPointer<RequestBase> >   HsRequest;
	typedef QHash<QLatin1String, QSharedPointer<SubscribeBase> > HsMessage;

class HbParser::Impl
{
public:
	FuncEmitMessage emitMessage;

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

void HbParser::InitParser(const FuncEmitMessage& emitMessage)
{
	m_pImpl->emitMessage = emitMessage;

// 
// 	m_pImpl->pIO = pIO;

	//////////////////////////////////////////////////////////////////////////

	RegRequest<ReqMarketDepthTop>();
	RegRequest<ReqMsgSubscribe>();
	RegRequest<ReqMsgUnsubscribe>();
	RegMessage<MsgTradeDetail>();
	RegMessage<MsgMarketDetail>();
	RegMessage<MsgLastKLine>();
	RegMessage<MsgLastTimeLine>();
	RegMessage<MsgMarketDepthDiff>();
	RegMessage<MsgMarketDepthTopDiff>();
	RegMessage<MsgMarketOverview>();
	RegMessage<MsgMarketStatic>();

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

	m_pImpl->emitMessage(szAttributeName[AN_REQUEST], json.toVariantMap());

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

				qDebug() << json[szAttributeName[AN_MSGTYPE]].toString();

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

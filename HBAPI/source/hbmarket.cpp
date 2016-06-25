#include "hbmarket.h"

#include <QMap>
#include <QJsonObject>
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
#include "req/reqmarketdepth.h"
#include "req/reqkline.h"



namespace HBAPI
{
	typedef QHash<QString, QSharedPointer<RequestBase> >   HsRequest;
	typedef QHash<QString, QSharedPointer<SubscribeBase> > HsMessage;

class HbMarket::Impl
{
public:
	FuncEmitMarket emitMessage;

	IdCreater<int> icRequestIndex;

	HsRequest hsRequest;
	HsMessage hsMessage;

};

HbMarket::HbMarket(QObject* parent)
: QObject(parent)
, m_pImpl(new Impl)
{
	
}

HbMarket::~HbMarket()
{

}

void HbMarket::SetSendFunc(const FuncEmitMarket& emitMessage)
{
	m_pImpl->emitMessage = emitMessage;

	//////////////////////////////////////////////////////////////////////////

	RegRequest<ReqMarketDepth>();
	RegRequest<ReqMarketDepthTop>();
	RegRequest<ReqKLine>();
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

void HbMarket::ParserRequest(const QJsonArray& returnValue)
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

				if (json[szAttributeName[AN_RETCODE]].toInt() != CODE_OK)
				{
					qDebug() << "ErrorCode:" << json[szAttributeName[AN_RETCODE]];
					break;
				}

				QString strMsgType = json[szAttributeName[AN_MSGTYPE]].toString();
				HsRequest::const_iterator ciFind = 
					m_pImpl->hsRequest.constFind(strMsgType);
				if (ciFind == m_pImpl->hsRequest.constEnd())
				{
					break;
				}

				(*ciFind)->ReceiveJson(json[szAttributeName[AN_PAYLOAD]].toObject());

			} while (0);

		}
	}
}

void HbMarket::RegRequestBase(const char* sz, RequestBase* pBase)
{
	pBase->SetSendFunc(std::bind(&HbMarket::Packer, this, std::placeholders::_1));
	m_pImpl->hsRequest[QString(sz)] = QSharedPointer<RequestBase>(pBase);
}

template<class T>
void HbMarket::PrintJson(const T& json)
{
	for (T::const_iterator citorjson = json.constBegin();
		citorjson != json.constEnd(); ++citorjson)
	{
		qDebug() << citorjson.key() << ":" << citorjson.value();
	}
}

int HbMarket::Packer(QJsonObject& json)
{
	int nRet = m_pImpl->icRequestIndex();

	json.insert(szAttributeName[AN_VERSION], PV_CURRENT);
	json.insert(szAttributeName[AN_REQUESTINDEX], nRet);

	m_pImpl->emitMessage(szAttributeName[AN_REQUEST], json.toVariantMap());

	return nRet;
}

RequestBase* HbMarket::QueryRequestBase(const char* sz) const
{
	return m_pImpl->hsRequest.value(QString(sz)).data();
}

void HbMarket::ParserMessage(const QJsonArray& returnValue)
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

				QString strMsgType = json[szAttributeName[AN_MSGTYPE]].toString();
				HsMessage::const_iterator ciFind =
					m_pImpl->hsMessage.constFind(strMsgType);
				if (ciFind == m_pImpl->hsMessage.constEnd())
				{
					break;
				}

				(*ciFind)->ReceiveJson(json[szAttributeName[AN_PAYLOAD]].toObject());

			} while (0);

		}
	}
}

void HbMarket::RegMessageBase(const char* sz, SubscribeBase* pBase)
{
	m_pImpl->hsMessage[QString(sz)] = QSharedPointer<SubscribeBase>(pBase);

}

SubscribeBase* HbMarket::QueryMessageBase(const char* sz) const
{
	return m_pImpl->hsMessage.value(QString(sz)).data();
}

}

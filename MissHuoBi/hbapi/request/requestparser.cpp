#include "requestparser.h"
#include <QtSocketIo>
#include <QMap>
#include <QJsonObject>
#include "requestbase.h"
#include "reqmarketdepthtop.h"



namespace HBAPI
{
	typedef std::function<void(const QJsonArray&)> Fp;
	typedef QHash<QString, QSharedPointer<RequestBase> > HsRequest;

class RequestParser::Impl
{
public:
	QSocketIoClient* pIO;

	HsRequest hsRequest;

};

RequestParser::RequestParser(QObject* parent)
: QObject(parent)
, m_pImpl(new Impl)
{
	
}

RequestParser::~RequestParser()
{

}

void RequestParser::InitParser(QSocketIoClient* pIO)
{
	Fp fp = std::bind(&RequestParser::Parser, this, std::placeholders::_1);
	pIO->on("request", fp);
	m_pImpl->pIO = pIO;

	//////////////////////////////////////////////////////////////////////////

	RegRequest<ReqMarketDepthTop>();
}

void RequestParser::Parser(const QJsonArray& returnValue)
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
				qDebug() << json["version"].toInt();
				if (json["version"].toInt() != 1)
				{
					break;
				}

				json["requestIndex"].toInt();

				HsRequest::const_iterator ciFind = 
					m_pImpl->hsRequest.constFind(json["msgType"].toString());
				if (ciFind == m_pImpl->hsRequest.constEnd())
				{
					break;
				}

				(*ciFind)->ReceiveJson(json);
// 				if (json["retCode"])
// 				{
// 
// 				}

			} while (0);

		}
	}
}

void RequestParser::RegRequestBase(const char* sz, RequestBase* pBase)
{
	m_pImpl->hsRequest[sz] = QSharedPointer<RequestBase>(pBase);
}


// 			for (QJsonObject::const_iterator citorjson = json.constBegin();
// 				citorjson != json.constEnd(); ++citorjson)
// 			{
// 				qDebug() << citorjson.key() << ":" << citorjson.value();
// 			}

}

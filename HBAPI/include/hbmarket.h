#ifndef __REQUESTPARSER_H__
#define __REQUESTPARSER_H__

#include "hbglobal.h"

#include <QObject>
#include <QScopedPointer>
#include <functional>


typedef std::function<void(const QString &, const QVariantMap &)> FuncEmitMessage;

namespace HBAPI
{
	class RequestBase;
	class SubscribeBase;

	class HBAPI_EXPORT HbMarket : public QObject
	{
	public:
		HbMarket(QObject* parent);
		~HbMarket();

		void InitParser(const FuncEmitMessage& emitMessage);

		template<class T>
		T* QueryRequest() const
		{
			return static_cast<T*>(QueryRequestBase(T::ReqType()));
		}

		template<class T>
		T* RegRequest()
		{
			T* p = new T;
			RegRequestBase(T::ReqType(), p);
			return p;
		}

		template<class T>
		T* QueryMessage() const
		{
			return static_cast<T*>(QueryMessageBase(T::MsgType()));
		}

		template<class T>
		T* RegMessage()
		{
			T* p = new T;
			RegMessageBase(T::MsgType(), p);
			return p;
		}

		void ParserRequest(const QJsonArray& returnValue);

		void ParserMessage(const QJsonArray& returnValue);

	protected:
		int Packer(QJsonObject& json);

		void RegRequestBase(const char* sz, RequestBase* pBase);
		RequestBase* QueryRequestBase(const char* sz) const;

		void RegMessageBase(const char* sz, SubscribeBase* pBase);
		SubscribeBase* QueryMessageBase(const char* sz) const;

		template<class T>
		void PrintJson(const T& json);

	private:
		class Impl;
		QScopedPointer<Impl> m_pImpl;
	};

}


#endif // __REQUESTPARSER_H__

#ifndef __REQUESTPARSER_H__
#define __REQUESTPARSER_H__

#include <QObject>
#include <QScopedPointer>

class QSocketIoClient;

namespace HBAPI
{
	class RequestBase;

	class RequestParser : public QObject
	{
	public:
		RequestParser(QObject* parent);
		~RequestParser();

		void InitParser(QSocketIoClient* pIO);

		template<class T>
		T* RegRequest()
		{
			T* p = new T;
			RegRequestBase(T::MsgType(), p);
			return p;
		}

	protected:
		void Parser(const QJsonArray& returnValue);

		void RegRequestBase(const char* sz, RequestBase* pBase);

	private:
		class Impl;
		QScopedPointer<Impl> m_pImpl;
	};

}


#endif // __REQUESTPARSER_H__

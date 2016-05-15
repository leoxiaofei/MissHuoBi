#ifndef __HBREST_H__
#define __HBREST_H__

#include "hbglobal.h"
#include <QObject>
#include <functional>

namespace HBAPI
{
	class RestError;

	class RestRequestBase;

	class MapKV;

	typedef std::function<long(const QByteArray& ba)> FuncEmitRest;

	class HBAPI_EXPORT HbRest : public QObject
	{
		Q_OBJECT
	public:
		HbRest(QObject* parent = 0);
		~HbRest();

		template<class T>
		T* QueryRequest() const
		{
			return static_cast<T*>(QueryRequestBase(T::RestType()));
		}

		template<class T>
		T* RegRequest()
		{
			T* p = new T;
			RegRequestBase(T::RestType(), p);
			return p;
		}

		void SetSendFunc(const FuncEmitRest& emitRest);

		void ParserRequest(long nRequestId, const QByteArray& ba);

		void SetKey(const QString& strAccessKey, const QString& strSecretKey);

	protected:
		void Packer(MapKV& mapParams, MapKV& mapExtra, RestRequestBase* pBase);
		QString CreateSign(MapKV& mapParams);

		void RegRequestBase(const char* sz, RestRequestBase* pBase);
		RestRequestBase* QueryRequestBase(const char* sz) const;

	signals:
		void signal_RestError(const QSharedPointer<RestError>& ptRestError);

	private:
		class Impl;
		QScopedPointer<Impl> m_pImpl;
	};

}
#endif // __HBREST_H__

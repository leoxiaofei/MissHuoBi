#ifndef __RESTREQUESTBASE_H__
#define __RESTREQUESTBASE_H__

#include <QObject>
#include <functional>
#include <QMap>
#include <QLatin1String>
#include <QVariant>
#include <QSharedPointer>

#include "hbglobal.h"
#include "common/misshbdef.h"


#define RESTTYPE(x) \
		public: \
			static const char* RestType() { return #x; } \
			virtual const char* GetRestType() const override { return RestType(); } \
		private:


namespace HBAPI
{
	class MapKV;
	class RestRequestBase;

	typedef std::function<void(MapKV&, MapKV&, RestRequestBase*)> SendRestFunc;

	class HBAPI_EXPORT RestRequestBase : public QObject
	{
	public:
		virtual const char* GetRestType() const = 0;
		virtual bool ReceiveJson(const QJsonDocument& json) = 0;

		void SetSendFunc(const SendRestFunc& funcSend);

	protected:
		void SendRest(MapKV& mapParams);
		void SendRest(MapKV& mapParams, MapKV& mapExtra);

	private:
		SendRestFunc m_funcSend;
	};

}




#endif // __RESTREQUESTBASE_H__

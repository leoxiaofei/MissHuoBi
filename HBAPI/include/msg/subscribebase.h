#ifndef __SUBSCRIBEBASE_H__
#define __SUBSCRIBEBASE_H__

#include <QJsonArray>
#include <QObject>

#include "common/misshbdef.h"
#include "hbglobal.h"

#define MSGTYPE(x) \
		public: \
			static const char* MsgType() { return #x; } \
			virtual const char* GetMsgType() const override { return MsgType(); } \
		private:

class QJsonObject;

namespace HBAPI
{
	class HBAPI_EXPORT Subscriber
	{
	public:
		Subscriber(const char* szMsgType = NULL);
		Subscriber(const char* szMsgType, const QJsonObject& json);
		~Subscriber();

		void AddJsonObject(const QJsonObject& json);

		void Apply(QJsonObject& jParent) const;

	private:
		const char* szMsgType;
		QJsonArray jsValue;
	};

	class HBAPI_EXPORT SubscribeBase : public QObject
	{
	public:
		virtual const char* GetMsgType() const = 0;
		virtual bool ReceiveJson(const QJsonObject& joPayload) = 0;

	};

}


#endif // __SUBSCRIBEBASE_H__

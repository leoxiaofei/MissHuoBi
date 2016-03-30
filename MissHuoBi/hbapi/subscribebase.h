#ifndef __SUBSCRIBEBASE_H__
#define __SUBSCRIBEBASE_H__

#include <QJsonArray>
#include "misshbdef.h"

#define MSGTYPE(x) \
		public: \
			static const char* MsgType() { return #x; } \
			virtual const char* GetMsgType() const override { return MsgType(); } \
		private:

class QJsonObject;

namespace HBAPI
{
	class SubscribeBase;

	class Subscriber
	{
	public:
		Subscriber(SubscribeBase* pBase = NULL);
		Subscriber(SubscribeBase* pBase, const QJsonObject& json);
		~Subscriber();

		void AddJsonObject(const QJsonObject& json);

		void Apply(QJsonObject& jParent) const;

	private:
		SubscribeBase* pSubscribeBase;
		QJsonArray jsValue;
	};

	class SubscribeBase
	{
	public:
		virtual const char* GetMsgType() const = 0;
		virtual bool ReceiveJson(const QJsonObject& joPayload) = 0;

	};

}


#endif // __SUBSCRIBEBASE_H__

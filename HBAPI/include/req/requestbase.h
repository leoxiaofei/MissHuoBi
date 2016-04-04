#ifndef __REQUESTBASE_H__
#define __REQUESTBASE_H__

#include <QString>
#include <functional>
#include "common/misshbdef.h"
#include "hbglobal.h"

class QJsonObject;

#define REQTYPE(x) \
		public: \
			static const char* ReqType() { return #x; } \
			virtual const char* GetReqType() const override { return ReqType(); } \
		private:

typedef std::function<int(QJsonObject&)> SendFunc;

namespace HBAPI
{
	class HBAPI_EXPORT RequestBase
	{
	public:
		virtual const char* GetReqType() const = 0;
		virtual bool ReceiveJson(const QJsonObject& json) = 0;

		void SetSendFunc(const SendFunc& funcSend);

	protected:
		virtual int SendJson(QJsonObject& json);

	private:
		SendFunc m_funcSend;
	};

}



#endif // __REQUESTBASE_H__

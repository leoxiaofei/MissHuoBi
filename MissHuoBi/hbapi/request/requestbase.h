#ifndef __REQUESTBASE_H__
#define __REQUESTBASE_H__

class QJsonObject;

#define MSGTYPE(x) \
		public: \
			static const char* MsgType() { return #x; } \
			virtual const char* GetMsgType() const override { return MsgType(); } \
		private:

namespace HBAPI
{
	class RequestBase
	{
	public:
		virtual const char* GetMsgType() const = 0;
		virtual bool ReceiveJson(const QJsonObject& json) = 0;

	protected:

	};

}



#endif // __REQUESTBASE_H__

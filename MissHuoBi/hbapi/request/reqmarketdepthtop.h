#ifndef __REQMARKETDEPTHTOP_H__
#define __REQMARKETDEPTHTOP_H__

#include "requestbase.h"


namespace HBAPI
{
	class ReqMarketDepthTop : public RequestBase
	{
		MSGTYPE(reqMarketDepthTop);
	public:
		ReqMarketDepthTop();
		~ReqMarketDepthTop();

		virtual bool ReceiveJson(const QJsonObject& json) override;

	};

}

#endif // __REQMARKETDEPTHTOP_H__

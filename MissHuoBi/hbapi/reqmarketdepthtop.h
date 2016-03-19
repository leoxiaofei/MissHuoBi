#ifndef __REQMARKETDEPTHTOP_H__
#define __REQMARKETDEPTHTOP_H__

#include "requestbase.h"

/*
历史数据接口
获取Top行情深度
*/

namespace HBAPI
{
	class ReqMarketDepthTop : public RequestBase
	{
		REQTYPE(reqMarketDepthTop);
	public:
		ReqMarketDepthTop();
		~ReqMarketDepthTop();

		int SendRequest(SymbolIdType eSymbolId);

	protected:
		virtual bool ReceiveJson(const QJsonObject& json) override;

	};

}

#endif // __REQMARKETDEPTHTOP_H__

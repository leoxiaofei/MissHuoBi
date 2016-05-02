#ifndef __REQMARKETDEPTHTOP_H__
#define __REQMARKETDEPTHTOP_H__

#include "requestbase.h"

#include <QSharedPointer>

/*
历史数据接口
获取Top行情深度
*/

namespace HBAPI
{
	class MarketDepthTopData;

	class HBAPI_EXPORT ReqMarketDepthTop : public RequestBase
	{
		Q_OBJECT
		REQTYPE(reqMarketDepthTop);
	public:
		ReqMarketDepthTop();
		~ReqMarketDepthTop();

		int SendRequest(SymbolIdType eSymbolId);

	protected:
		virtual bool ReceiveJson(const QJsonObject& json) override;

	signals:
		void signal_Receive(const QSharedPointer<MarketDepthTopData>& ptMarketDepthTopData);
	};

}

#endif // __REQMARKETDEPTHTOP_H__

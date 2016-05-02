#ifndef __REQMARKETDEPTHTOP_H__
#define __REQMARKETDEPTHTOP_H__

#include "requestbase.h"

#include <QSharedPointer>

/*
��ʷ���ݽӿ�
��ȡTop�������
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

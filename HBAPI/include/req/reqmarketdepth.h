#ifndef __REQMARKETDEPTH_H__
#define __REQMARKETDEPTH_H__

#include "requestbase.h"
#include <QSharedPointer>

/*
��ʷ���ݽӿ�
��ȡ�������
*/

namespace HBAPI
{
	class MarketDepthData;

	class HBAPI_EXPORT ReqMarketDepth : public RequestBase
	{
		Q_OBJECT
		REQTYPE(reqMarketDepth);
	public:
		ReqMarketDepth();
		~ReqMarketDepth();

		int SendRequest(SymbolIdType eSymbolId, PercentType ePercentType);

	protected:
		virtual bool ReceiveJson(const QJsonObject& json) override;

	signals:
		void signal_Receive(const QSharedPointer<MarketDepthData>& ptMarketDepthData);

	};

}

#endif // __REQMARKETDEPTH_H__

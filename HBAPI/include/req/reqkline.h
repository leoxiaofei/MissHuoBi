#ifndef __REQKLINE_H__
#define __REQKLINE_H__

#include "requestbase.h"
#include <QSharedPointer>

class QDateTime;

/*
��ʷ���ݽӿ�
��ȡ��ʷk����Ϣ
*/

namespace HBAPI
{
	class KLineData;

	class HBAPI_EXPORT ReqKLine : public RequestBase
	{
		Q_OBJECT
		REQTYPE(reqKLine);
	public:
		ReqKLine();
		~ReqKLine();

		int SendRequest(SymbolIdType eSymbolId, PeriodType ePercentType, 
			const QDateTime& dtFrom, const QDateTime& dtTo);

	protected:
		virtual bool ReceiveJson(const QJsonObject& json) override;

	signals:
		void signal_Receive(const QSharedPointer<KLineData>& ptMarketDepthData);

	};

}
#endif // __REQKLINE_H__

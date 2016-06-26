#ifndef __REQTIMELINE_H__
#define __REQTIMELINE_H__


#include "requestbase.h"

#include <QSharedPointer>

/*
��ʷ���ݽӿ�
��ȡ��ʷ��ʱ����
*/

namespace HBAPI
{
	class TimeLineData;

	class HBAPI_EXPORT ReqTimeLine : public RequestBase
	{
		Q_OBJECT
		REQTYPE(reqTimeLine);
	public:
		ReqTimeLine();
		~ReqTimeLine();

		int SendRequest(SymbolIdType eSymbolId, const QDateTime& dtFrom, const QDateTime& dtTo);

	protected:
		virtual bool ReceiveJson(const QJsonObject& json) override;

	signals:
		void signal_Receive(const QSharedPointer<TimeLineData>& ptMarketDepthData);

	};

}

#endif // __REQTIMELINE_H__

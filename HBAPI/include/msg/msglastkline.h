#ifndef __MSGLASKKLINE_H__
#define __MSGLASKKLINE_H__


#include "subscribebase.h"

#include <QVector>

namespace HBAPI
{
	class LastKLineData;

	class HBAPI_EXPORT MsgLastKLine : public SubscribeBase
	{
		Q_OBJECT
		MSGTYPE(lastKLine);
	public:
		static Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType,
			const QVector<PeriodType>& vecPeriodType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	signals :
		void signal_Receive(const QSharedPointer<LastKLineData>& ptLastKLineData);

	};

}

#endif // __MSGLASKKLINE_H__

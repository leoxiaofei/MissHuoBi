#ifndef __MSGLASKKLINE_H__
#define __MSGLASKKLINE_H__


#include "subscribebase.h"

#include <QVector>

namespace HBAPI
{
	class MsgLastKLine : public SubscribeBase
	{
		MSGTYPE(lastKLine);
	public:
		Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType,
			const QVector<PeriodType>& vecPeriodType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	};

}

#endif // __MSGLASKKLINE_H__

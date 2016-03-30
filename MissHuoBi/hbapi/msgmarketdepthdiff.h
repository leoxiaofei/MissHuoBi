#ifndef __MSGMARKETDEPTHDIFF_H__
#define __MSGMARKETDEPTHDIFF_H__

#include "subscribebase.h"

#include <QVector>

namespace HBAPI
{
	class MsgMarketDepthDiff : public SubscribeBase
	{
		MSGTYPE(marketDepthDiff);
	public:
		Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType,
			const QVector<PercentType>& vecPercentType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	};

}

#endif // __MSGMARKETDEPTHDIFF_H__
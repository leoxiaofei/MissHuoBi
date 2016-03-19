#ifndef __TRADEDETAIL_H__
#define __TRADEDETAIL_H__

#include "subscribebase.h"
#include "misshbdef.h"

namespace HBAPI
{


	class TradeDetail : public SubscribeBase
	{
		MSGTYPE(tradeDetail);
	public:
		Subscriber GetSubscriber(const QString& symbolId, PushType ePushType);

	};

}


#endif // __TRADEDETAIL_H__

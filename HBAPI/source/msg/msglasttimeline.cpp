#include "msg/msglasttimeline.h"
#include "tools/mspool.hpp"
#include "common/misshbdef.h"
#include "common/misshbfunc.h"

#include <QJsonObject>
#include <QSharedPointer>

namespace HBAPI
{
	typedef MsPool<class Tag, LastTimeLineData> MPLTLD;

	Subscriber MsgLastTimeLine::GetSubscriber(SymbolIdType eSymbolId, PushType ePushType)
	{
		QJsonObject js;
		js.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
		js.insert(szAttributeName[AN_PUSHTYPE], szPushType[ePushType]);

		return Subscriber(MsgType(), js);
	}

	bool MsgLastTimeLine::ReceiveJson(const QJsonObject& joPayload)
	{
		QSharedPointer<LastTimeLineData> ptLastTimeLineData(MPLTLD::New(), &MPLTLD::Free);

		ptLastTimeLineData->eSymbolId = GetSymbolIdType(joPayload[szAttributeName[AN_SYMBOLID]].toString());
		ptLastTimeLineData->tTime = joPayload[szAttributeName[AN_TIME]].toDouble();
		ptLastTimeLineData->dPriceLast = joPayload[szAttributeName[AN_PRICELAST]].toDouble();
		ptLastTimeLineData->dAmount = joPayload[szAttributeName[AN_AMOUNT]].toDouble();
		ptLastTimeLineData->dVolume = joPayload[szAttributeName[AN_VOLUME]].toDouble();
		ptLastTimeLineData->nCount = joPayload[szAttributeName[AN_COUNT]].toDouble();

		emit signal_Receive(ptLastTimeLineData);
		return true;
	}

}

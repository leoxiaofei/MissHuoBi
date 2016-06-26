#include "msg/msglasttimeline.h"
#include "tools/mspool.hpp"
#include "common/misshbdef.h"
#include "common/misshbfunc.h"
#include "common/timelinedata.h"

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

		ParseTimeLineCylinder(joPayload, *ptLastTimeLineData);

		emit signal_Receive(ptLastTimeLineData);

		return true;
	}

}

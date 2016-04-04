#include "msg/msgmarketdepthtopdiff.h"
#include "tools/mspool.hpp"
#include "common/misshbfunc.h"

#include <QJsonObject>
#include <QSharedPointer>
#include <QVariant>

namespace HBAPI
{
	typedef MsPool<class Tag, MarketDepthTopDiffData> MPMDTDD;

	Subscriber MsgMarketDepthTopDiff::GetSubscriber(SymbolIdType eSymbolId, PushType ePushType)
	{
		QJsonObject js;
		js.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
		js.insert(szAttributeName[AN_PUSHTYPE], szPushType[ePushType]);

		return Subscriber(MsgType(), js);
	}

	bool MsgMarketDepthTopDiff::ReceiveJson(const QJsonObject& joPayload)
	{
		QSharedPointer<MarketDepthTopDiffData> ptMarketDepthTopDiffData(MPMDTDD::New(), &MPMDTDD::Free);

		ptMarketDepthTopDiffData->eSymbolId = GetSymbolIdType(joPayload[szAttributeName[AN_SYMBOLID]].toString());
		ptMarketDepthTopDiffData->uVersion = joPayload[szAttributeName[AN_VERSION]].toVariant().toULongLong();
		ptMarketDepthTopDiffData->uVersionOld = joPayload[szAttributeName[AN_VERSIONOLD]].toVariant().toULongLong();

		ParseAskInsertData(joPayload[szAttributeName[AN_ASKINSERT]].toObject(), ptMarketDepthTopDiffData->vecAskInsertData);
		ParsAskDeleteData(joPayload[szAttributeName[AN_ASKDELETE]].toArray(), ptMarketDepthTopDiffData->vecAskDeleteData);
		ParseAskUpdateData(joPayload[szAttributeName[AN_ASKUPDATE]].toObject(), ptMarketDepthTopDiffData->vecAskUpdateData);

		ParseBidInsertData(joPayload[szAttributeName[AN_BIDINSERT]].toObject(), ptMarketDepthTopDiffData->vecBidInsertData);
		ParseBidDeleteData(joPayload[szAttributeName[AN_BIDDELETE]].toArray(), ptMarketDepthTopDiffData->vecBidDeleteData);
		ParseBidUpdateData(joPayload[szAttributeName[AN_BIDUPDATE]].toObject(), ptMarketDepthTopDiffData->vecBidUpdateData);

		return false;

	}

}
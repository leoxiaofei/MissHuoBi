#include "msg/msgmarketdepthdiff.h"

#include "tools/mspool.hpp"
#include "common/misshbfunc.h"

#include <QJsonObject>
#include <QSharedPointer>
#include <QVariant>

namespace HBAPI
{
	typedef MsPool<class Tag, MarketDepthDiffData> MPMDDD;

	Subscriber MsgMarketDepthDiff::GetSubscriber(SymbolIdType eSymbolId, 
		PushType ePushType, const QVector<PercentType>& vecPercentType)
	{
		Subscriber sRet(MsgType());

		for (int ix = 0; ix != vecPercentType.size(); ++ix)
		{
			QJsonObject js;

			js.insert(szAttributeName[AN_SYMBOLID], szSymbolIdType[eSymbolId]);
			js.insert(szAttributeName[AN_PUSHTYPE], szPushType[ePushType]);
			js.insert(szAttributeName[AN_PERCENT], szPercentType[vecPercentType[ix]]);

			sRet.AddJsonObject(js);
		}

		return sRet;
	}

	bool MsgMarketDepthDiff::ReceiveJson(const QJsonObject& joPayload)
	{
		QSharedPointer<MarketDepthDiffData> ptMarketDepthDiffData(MPMDDD::New(), &MPMDDD::Free);

		ptMarketDepthDiffData->eSymbolId = GetSymbolIdType(joPayload[szAttributeName[AN_SYMBOLID]].toString());
		ptMarketDepthDiffData->ePercentType = GetPercentType(joPayload[szAttributeName[AN_PERCENT]].toString());
		ptMarketDepthDiffData->uVersion = joPayload[szAttributeName[AN_VERSION]].toVariant().toULongLong();
		ptMarketDepthDiffData->uVersionOld = joPayload[szAttributeName[AN_VERSIONOLD]].toVariant().toULongLong();

		ParseAskInsertData(joPayload[szAttributeName[AN_ASKINSERT]].toObject(), ptMarketDepthDiffData->vecAskInsertData);
		ParsAskDeleteData(joPayload[szAttributeName[AN_ASKDELETE]].toArray(), ptMarketDepthDiffData->vecAskDeleteData);
		ParseAskUpdateData(joPayload[szAttributeName[AN_ASKUPDATE]].toObject(), ptMarketDepthDiffData->vecAskUpdateData);

		ParseBidInsertData(joPayload[szAttributeName[AN_BIDINSERT]].toObject(), ptMarketDepthDiffData->vecBidInsertData);
		ParseBidDeleteData(joPayload[szAttributeName[AN_BIDDELETE]].toArray(), ptMarketDepthDiffData->vecBidDeleteData);
		ParseBidUpdateData(joPayload[szAttributeName[AN_BIDUPDATE]].toObject(), ptMarketDepthDiffData->vecBidUpdateData);

		return false;

	}

}

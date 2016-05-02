#include "common\marketdepthdata.h"
#include "common\misshbfunc.h"

#include <QJsonObject>


namespace HBAPI
{
	void ParseMarketDepthData(const QJsonObject& joPayload, MarketDepthData& mdd)
	{
		mdd.eSymbolId = GetSymbolIdType(joPayload[szAttributeName[AN_SYMBOLID]].toString());
		mdd.ePercent = GetPercentType(joPayload[szAttributeName[AN_PERCENT]].toString());
		mdd.tTime = joPayload[szAttributeName[AN_TIME]].toDouble();
		mdd.uVersion = joPayload[szAttributeName[AN_VERSION]].toDouble();

		ParseAskDepthData(joPayload, mdd.listAskDepthData);
		ParseBidDepthData(joPayload, mdd.listBidDepthData);

	}

}

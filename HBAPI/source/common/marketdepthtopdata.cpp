#include "common\marketdepthtopdata.h"
#include "common\misshbfunc.h"

#include <QJsonObject>


namespace HBAPI
{
	void ParseMarketDepthTopData(const QJsonObject& joPayload, MarketDepthTopData& mdtd)
	{
		mdtd.eSymbolId = GetSymbolIdType(joPayload[szAttributeName[AN_SYMBOLID]].toString());
		mdtd.tTime = joPayload[szAttributeName[AN_TIME]].toDouble();
		mdtd.uVersion = joPayload[szAttributeName[AN_VERSION]].toDouble();

		ParseAskDepthData(joPayload, mdtd.listAskDepthData);
		ParseBidDepthData(joPayload, mdtd.listBidDepthData);

	}

}

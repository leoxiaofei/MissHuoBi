#include "rest\restgetaccountinfo.h"
#include "common\mapkv.h"
#include "tools\mspool.hpp"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

namespace HBAPI
{
	namespace
	{
		enum ElemText { ET_AVAILABLE_BTC_DISPLAY, ET_LOAN_CNY_DISPLAY, 
			ET_FROZEN_CNY_DISPLAY, ET_AVAILABLE_LTC_DISPLAY, ET_LOAN_BTC_DISPLAY, 
			ET_FROZEN_BTC_DISPLAY, ET_NET_ASSET, ET_LOAN_LTC_DISPLAY, 
			ET_FROZEN_LTC_DISPLAY, ET_AVAILABLE_CNY_DISPLAY, ET_TOTAL };

		const char* szElemText[] =
		{
			"available_btc_display",
			"loan_cny_display",
			"frozen_cny_display",
			"available_ltc_display",
			"loan_btc_display",
			"frozen_btc_display",
			"net_asset",
			"loan_ltc_display",
			"frozen_ltc_display",
			"available_cny_display",
			"total",
		};

	}

	typedef MsPool<class Tag, AccountInfoData> MPAID;

	void RestGetAccountInfo::SendRequest(MarketType eMarketType)
	{
		MapKV mapParams;

		if (eMarketType != MT_CNY)
		{
			MapKV mapExtra;
			mapExtra.insert(szRestKName[RK_MARKET], szMarketType[eMarketType]);
			SendRest(mapParams, mapExtra);
		}
		else
		{
			SendRest(mapParams);
		}
	}

	bool RestGetAccountInfo::ReceiveJson(const QJsonDocument& json, int nCode)
	{
		AccountInfoData* pData = MPAID::New();

		QJsonObject obj = json.object();

		pData->dAvailableBtcDisplay = obj[szElemText[ET_AVAILABLE_BTC_DISPLAY]].toString().toDouble();
		pData->dLoanCnyDisplay = obj[szElemText[ET_LOAN_CNY_DISPLAY]].toString().toDouble();
		pData->dFrozenCnyDisplay = obj[szElemText[ET_FROZEN_CNY_DISPLAY]].toString().toDouble();
		pData->dAvailableLtcDisplay = obj[szElemText[ET_AVAILABLE_LTC_DISPLAY]].toString().toDouble();
		pData->dLoanBtcDisplay = obj[szElemText[ET_LOAN_BTC_DISPLAY]].toString().toDouble();
		pData->dFrozenBtcDisplay = obj[szElemText[ET_FROZEN_BTC_DISPLAY]].toString().toDouble();
		pData->dNetAsset = obj[szElemText[ET_NET_ASSET]].toString().toDouble();
		pData->dLoanLtcDisplay = obj[szElemText[ET_LOAN_LTC_DISPLAY]].toString().toDouble();
		pData->dFrozenLtcDisplay = obj[szElemText[ET_FROZEN_LTC_DISPLAY]].toString().toDouble();
		pData->dAvailableCnyDisplay = obj[szElemText[ET_AVAILABLE_CNY_DISPLAY]].toString().toDouble();
		pData->dTotal = obj[szElemText[ET_TOTAL]].toString().toDouble();

		emit signal_Receive(QSharedPointer<AccountInfoData>(pData, &MPAID::Free));

		return true;
	}

}


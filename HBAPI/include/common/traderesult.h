#ifndef __TRADERESULT_H__
#define __TRADERESULT_H__

#include "hbglobal.h"

class QJsonDocument;

namespace HBAPI
{
	class HBAPI_EXPORT TradeResult
	{
	public:
		unsigned int uOrderId;
		bool		 bResult;
	};

	void ParseTradeResult(const QJsonDocument& json, TradeResult& tTradeResult);

}



#endif // __TRADERESULT_H__

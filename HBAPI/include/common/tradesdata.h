#ifndef __TRADESDATA_H__
#define __TRADESDATA_H__

#include <QVector>

#include "misshbdef.h"
#include "hbglobal.h"

class QJsonObject;

namespace HBAPI
{

	///成交单
	class HBAPI_EXPORT TradesData
	{
	public:
		double					dPrice;				///价格
		double					dAmount;			///成交量
		time_t					tTime;				///时间
		DirectionType			eDirection;			///交易方向：买入和卖出
	};


	void ParseTradesData(const QJsonObject& json, QVector<TradesData>& vecTradesData);


}


#endif // __TRADESDATA_H__

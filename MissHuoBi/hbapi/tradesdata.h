#ifndef __TRADESDATA_H__
#define __TRADESDATA_H__

#include <boost\rational.hpp>
#include <QVector>

#include "misshbdef.h"

class QJsonObject;

namespace HBAPI
{

	///成交单
	class TradesData
	{
	public:
		boost::rational<int>	rPrice;				///价格
		time_t					tTime;				///时间
		boost::rational<int>	rAmount;			///成交量
		DirectionType			eDirection;			///交易方向：买入和卖出
	};


	void ParseTradesData(const QJsonObject& json, QVector<TradesData>& vecTradesData);


}


#endif // __TRADESDATA_H__

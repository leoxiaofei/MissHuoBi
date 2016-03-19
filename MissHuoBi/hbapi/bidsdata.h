#ifndef __BIDSDATA_H__
#define __BIDSDATA_H__

#include <boost\rational.hpp>
#include <QVector>

class QJsonObject;

namespace HBAPI
{

///买单
class BidsData
{
public:
	boost::rational<int>	rPrice;				///价格
	boost::rational<int>	rAmount;			///成交量
	boost::rational<int>	rAccuAmount;		///累计委单量
	int32_t					nLevel;
};


void ParseBidsData(const QJsonObject& json, QVector<BidsData>& vecBidsData);



}

#endif // __BIDSDATA_H__

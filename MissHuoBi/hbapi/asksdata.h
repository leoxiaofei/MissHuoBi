#ifndef __ASKSDATA_H__
#define __ASKSDATA_H__


#include <boost\rational.hpp>
#include <QVector>

class QJsonObject;


namespace HBAPI
{

///卖单
class AsksData
{
public:
	boost::rational<int>	rPrice;				///价格
	boost::rational<int>	rAmount;			///成交量
	boost::rational<int>	rAccuAmount;		///累计委单量
	int32_t					nLevel;
};


void ParseAsksData(const QJsonObject& json, QVector<AsksData>& vecAsksData);



}

#endif // __ASKSDATA_H__

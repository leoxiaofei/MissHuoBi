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
	double	dPrice;				///价格
	double	dAmount;			///成交量
	double	dAccuAmount;		///累计委单量
	double	dLevel;
};


void ParseBidsData(const QJsonObject& json, QVector<BidsData>& vecBidsData);



}

#endif // __BIDSDATA_H__

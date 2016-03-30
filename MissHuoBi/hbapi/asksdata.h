#ifndef __ASKSDATA_H__
#define __ASKSDATA_H__


#include <QVector>

class QJsonObject;


namespace HBAPI
{

///卖单
class AsksData
{
public:
	double	dPrice;				///价格
	double	dAmount;			///成交量
	double	dAccuAmount;		///累计委单量
	double	dLevel;				///（猜想）涨跌量：最新价减去开盘价
};


void ParseAsksData(const QJsonObject& json, QVector<AsksData>& vecAsksData);



}

#endif // __ASKSDATA_H__

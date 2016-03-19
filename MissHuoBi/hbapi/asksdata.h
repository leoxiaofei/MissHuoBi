#ifndef __ASKSDATA_H__
#define __ASKSDATA_H__


#include <boost\rational.hpp>
#include <QVector>

class QJsonObject;


namespace HBAPI
{

///����
class AsksData
{
public:
	boost::rational<int>	rPrice;				///�۸�
	boost::rational<int>	rAmount;			///�ɽ���
	boost::rational<int>	rAccuAmount;		///�ۼ�ί����
	int32_t					nLevel;
};


void ParseAsksData(const QJsonObject& json, QVector<AsksData>& vecAsksData);



}

#endif // __ASKSDATA_H__

#ifndef __BIDSDATA_H__
#define __BIDSDATA_H__

#include <boost\rational.hpp>
#include <QVector>

class QJsonObject;

namespace HBAPI
{

///��
class BidsData
{
public:
	boost::rational<int>	rPrice;				///�۸�
	boost::rational<int>	rAmount;			///�ɽ���
	boost::rational<int>	rAccuAmount;		///�ۼ�ί����
	int32_t					nLevel;
};


void ParseBidsData(const QJsonObject& json, QVector<BidsData>& vecBidsData);



}

#endif // __BIDSDATA_H__

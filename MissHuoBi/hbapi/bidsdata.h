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
	double	dPrice;				///�۸�
	double	dAmount;			///�ɽ���
	double	dAccuAmount;		///�ۼ�ί����
	double	dLevel;
};


void ParseBidsData(const QJsonObject& json, QVector<BidsData>& vecBidsData);



}

#endif // __BIDSDATA_H__

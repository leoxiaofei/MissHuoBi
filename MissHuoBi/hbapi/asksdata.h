#ifndef __ASKSDATA_H__
#define __ASKSDATA_H__


#include <QVector>

class QJsonObject;


namespace HBAPI
{

///����
class AsksData
{
public:
	double	dPrice;				///�۸�
	double	dAmount;			///�ɽ���
	double	dAccuAmount;		///�ۼ�ί����
	double	dLevel;				///�����룩�ǵ��������¼ۼ�ȥ���̼�
};


void ParseAsksData(const QJsonObject& json, QVector<AsksData>& vecAsksData);



}

#endif // __ASKSDATA_H__

#ifndef __TRADESDATA_H__
#define __TRADESDATA_H__

#include <QVector>

#include "misshbdef.h"
#include "hbglobal.h"

class QJsonObject;

namespace HBAPI
{

	///�ɽ���
	class HBAPI_EXPORT TradesData
	{
	public:
		double					dPrice;				///�۸�
		double					dAmount;			///�ɽ���
		time_t					tTime;				///ʱ��
		DirectionType			eDirection;			///���׷������������
	};


	void ParseTradesData(const QJsonObject& json, QVector<TradesData>& vecTradesData);


}


#endif // __TRADESDATA_H__

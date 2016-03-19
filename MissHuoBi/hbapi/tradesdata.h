#ifndef __TRADESDATA_H__
#define __TRADESDATA_H__

#include <boost\rational.hpp>
#include <QVector>

#include "misshbdef.h"

class QJsonObject;

namespace HBAPI
{

	///�ɽ���
	class TradesData
	{
	public:
		boost::rational<int>	rPrice;				///�۸�
		time_t					tTime;				///ʱ��
		boost::rational<int>	rAmount;			///�ɽ���
		DirectionType			eDirection;			///���׷������������
	};


	void ParseTradesData(const QJsonObject& json, QVector<TradesData>& vecTradesData);


}


#endif // __TRADESDATA_H__

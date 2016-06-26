#ifndef __KLINEDATA_H__
#define __KLINEDATA_H__

#include "hbglobal.h"
#include "misshbdef.h"

#include <time.h>
#include <QVector>

class QJsonObject;

namespace HBAPI
{
	class HBAPI_EXPORT TimeLineCylinder
	{
	public:
		time_t			tTime;			   //时间，秒数
		double			dPriceLast;		   //收盘
		double			dAmount;		   //成交量
		double			dVolume;		   //成交额
		int				nCount;			   //成交笔数
	};

	void ParseTimeLineCylinder(const QJsonObject& json, TimeLineCylinder& cylinder);
	void ParseTimeLineCylinder(const QJsonObject& json, QVector<TimeLineCylinder>& vecCylinder);

	class HBAPI_EXPORT TimeLineData
	{
	public:
		SymbolIdType				eSymbolId;			///交易代码
		QVector<TimeLineCylinder>	vecCylinder;		///柱状图数据
	};

	void ParseTimeLineCylinder(const QJsonObject& json, TimeLineData& timeLineData);

	class HBAPI_EXPORT LastTimeLineData
	{
	public:
		SymbolIdType		eSymbolId;		   //交易代码
		TimeLineCylinder	cylinder;
	};

	void ParseTimeLineCylinder(const QJsonObject& json, LastTimeLineData& lastTimeLineData);

}


#endif // __KLINEDATA_H__

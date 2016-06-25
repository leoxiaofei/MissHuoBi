#ifndef __KLINEDATA_H__
#define __KLINEDATA_H__

#include "hbglobal.h"
#include "misshbdef.h"

#include <time.h>
#include <QVector>

class QJsonObject;

namespace HBAPI
{
	class HBAPI_EXPORT KLineCylinder
	{
	public:
		double			dPriceOpen;		   ///开盘
		double			dPriceHigh;		   ///最高
		double			dPriceLow;		   ///最低
		double			dPriceLast;		   ///收盘
		double			dAmount;		   ///成交量
		double			dVolume;		   ///成交额
		time_t			tTime;			   ///时间
		int				nCount;			   ///成交笔数
	};

	void ParseKLineCylinder(const QJsonObject& json, KLineCylinder& cylinder);
	void ParseKLineCylinder(const QJsonObject& json, QVector<KLineCylinder>& vecCylinder);

	class KLineData
	{
	public:
		SymbolIdType			eSymbolId;			///交易代码
		PeriodType				ePeriod;			///k线周期
		QVector<KLineCylinder>	vecCylinder;		///柱状图数据
	};

	void ParseKLineData(const QJsonObject& json, KLineData& cylinder);

	class HBAPI_EXPORT LastKLineData
	{
	public:
		SymbolIdType	eSymbolId;			///交易代码
		PeriodType		ePeriod;			///k线周期
		KLineCylinder	cylinder;			///柱状图数据
	};

	void ParseLastKLineData(const QJsonObject& json, LastKLineData& cylinder);

}


#endif // __KLINEDATA_H__

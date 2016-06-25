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
		double			dPriceOpen;		   ///����
		double			dPriceHigh;		   ///���
		double			dPriceLow;		   ///���
		double			dPriceLast;		   ///����
		double			dAmount;		   ///�ɽ���
		double			dVolume;		   ///�ɽ���
		time_t			tTime;			   ///ʱ��
		int				nCount;			   ///�ɽ�����
	};

	void ParseKLineCylinder(const QJsonObject& json, KLineCylinder& cylinder);
	void ParseKLineCylinder(const QJsonObject& json, QVector<KLineCylinder>& vecCylinder);

	class KLineData
	{
	public:
		SymbolIdType			eSymbolId;			///���״���
		PeriodType				ePeriod;			///k������
		QVector<KLineCylinder>	vecCylinder;		///��״ͼ����
	};

	void ParseKLineData(const QJsonObject& json, KLineData& cylinder);

	class HBAPI_EXPORT LastKLineData
	{
	public:
		SymbolIdType	eSymbolId;			///���״���
		PeriodType		ePeriod;			///k������
		KLineCylinder	cylinder;			///��״ͼ����
	};

	void ParseLastKLineData(const QJsonObject& json, LastKLineData& cylinder);

}


#endif // __KLINEDATA_H__

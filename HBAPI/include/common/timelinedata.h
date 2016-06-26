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
		time_t			tTime;			   //ʱ�䣬����
		double			dPriceLast;		   //����
		double			dAmount;		   //�ɽ���
		double			dVolume;		   //�ɽ���
		int				nCount;			   //�ɽ�����
	};

	void ParseTimeLineCylinder(const QJsonObject& json, TimeLineCylinder& cylinder);
	void ParseTimeLineCylinder(const QJsonObject& json, QVector<TimeLineCylinder>& vecCylinder);

	class HBAPI_EXPORT TimeLineData
	{
	public:
		SymbolIdType				eSymbolId;			///���״���
		QVector<TimeLineCylinder>	vecCylinder;		///��״ͼ����
	};

	void ParseTimeLineCylinder(const QJsonObject& json, TimeLineData& timeLineData);

	class HBAPI_EXPORT LastTimeLineData
	{
	public:
		SymbolIdType		eSymbolId;		   //���״���
		TimeLineCylinder	cylinder;
	};

	void ParseTimeLineCylinder(const QJsonObject& json, LastTimeLineData& lastTimeLineData);

}


#endif // __KLINEDATA_H__

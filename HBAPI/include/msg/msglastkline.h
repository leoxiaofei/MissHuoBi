#ifndef __MSGLASKKLINE_H__
#define __MSGLASKKLINE_H__


#include "subscribebase.h"

#include <QVector>

namespace HBAPI
{
	class HBAPI_EXPORT LastKLineData
	{
	public:
		SymbolIdType	eSymbolId;		   ///���״���
		PeriodType		ePeriod;		   ///k������
		time_t			tTime;			   ///ʱ��
		double			dPriceOpen;		   ///����
		double			dPriceHigh;		   ///���
		double			dPriceLow;		   ///���
		double			dPriceLast;		   ///����
		double			dAmount;		   ///�ɽ���
		double			dVolume;		   ///�ɽ���
		int				nCount;			   ///�ɽ�����
	};

	class HBAPI_EXPORT MsgLastKLine : public SubscribeBase
	{
		MSGTYPE(lastKLine);
	public:
		static Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType,
			const QVector<PeriodType>& vecPeriodType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	};

}

#endif // __MSGLASKKLINE_H__

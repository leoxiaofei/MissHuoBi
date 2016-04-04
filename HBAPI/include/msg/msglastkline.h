#ifndef __MSGLASKKLINE_H__
#define __MSGLASKKLINE_H__


#include "subscribebase.h"

#include <QVector>

namespace HBAPI
{
	class HBAPI_EXPORT LastKLineData
	{
	public:
		SymbolIdType	eSymbolId;		   ///交易代码
		PeriodType		ePeriod;		   ///k线周期
		time_t			tTime;			   ///时间
		double			dPriceOpen;		   ///开盘
		double			dPriceHigh;		   ///最高
		double			dPriceLow;		   ///最低
		double			dPriceLast;		   ///收盘
		double			dAmount;		   ///成交量
		double			dVolume;		   ///成交额
		int				nCount;			   ///成交笔数
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

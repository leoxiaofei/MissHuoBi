#ifndef __MSGLASTTIMELINE_H__
#define __MSGLASTTIMELINE_H__

#include "subscribebase.h"

#include <QVector>

namespace HBAPI
{
	class HBAPI_EXPORT LastTimeLineData
	{
	public:
		SymbolIdType	eSymbolId;		   //交易代码
		time_t			tTime;			   //时间，秒数
		double			dPriceLast;		   //收盘
		double			dAmount;		   //成交量
		double			dVolume;		   //成交额
		int				nCount;			   //成交笔数
	};

	class HBAPI_EXPORT MsgLastTimeLine : public SubscribeBase
	{
		MSGTYPE(lastTimeLine);
		Q_OBJECT
	public:
		static Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	signals :
		void signal_Receive(const QSharedPointer<LastTimeLineData>& ptMarketDepthDiffData);
	};

}

#endif // __MSGLASTTIMELINE_H__

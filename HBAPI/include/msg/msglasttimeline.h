#ifndef __MSGLASTTIMELINE_H__
#define __MSGLASTTIMELINE_H__

#include "subscribebase.h"

#include <QVector>

namespace HBAPI
{
	class HBAPI_EXPORT LastTimeLineData
	{
	public:
		SymbolIdType	eSymbolId;		   //���״���
		time_t			tTime;			   //ʱ�䣬����
		double			dPriceLast;		   //����
		double			dAmount;		   //�ɽ���
		double			dVolume;		   //�ɽ���
		int				nCount;			   //�ɽ�����
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

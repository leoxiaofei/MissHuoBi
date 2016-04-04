#ifndef __MSGMARKETOVERVIEW_H__
#define __MSGMARKETOVERVIEW_H__


#include "subscribebase.h"

namespace HBAPI
{
	class HBAPI_EXPORT MarketOverviewData
	{
	public:
		SymbolIdType				eSymbolId;				   ///���״���
		double						dPriceNew;				   ///��ǰ�۸�
		double						dPriceOpen;				   ///����
		double						dPriceHigh;				   ///���
		double						dPriceLow;				   ///���
		double						dPriceAsk;				   ///��һ
		double						dPriceBid;				   ///��һ
		double						dTotalVolume;			   ///�����ۼƳɽ���
		double						dTotalAmount;			   ///�����ۼƳɽ���
	};

	class HBAPI_EXPORT MsgMarketOverview : public SubscribeBase
	{
		Q_OBJECT
		MSGTYPE(marketOverview);
	public:
		MsgMarketOverview();
		~MsgMarketOverview();

		static Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	signals:
		void signal_Receive(const QSharedPointer<MarketOverviewData>& ptMarketOverviewData);

	};

}


#endif // __MSGMARKETOVERVIEW_H__
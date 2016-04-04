#ifndef __TRADEDETAIL_H__
#define __TRADEDETAIL_H__

#include "msg/subscribebase.h"
#include "common/misshbdef.h"
#include "common/bidsdata.h"
#include "common/asksdata.h"

#include <QVector>

namespace HBAPI
{
	class HBAPI_EXPORT TradeDetailData
	{
	public:
		int						nTradeId;			///����id
		time_t					tTime;
		double					dPrice;				///�۸�
		double					dAmount;			///�ɽ���
		DirectionType			eDirection;			///���׷������������

		QVector<BidsData>		vecTopBidsData;		///Top��
		QVector<AsksData>		vecTopAsksData;		///Top����
	};

	class HBAPI_EXPORT TradeDetailBill
	{
	public:
		SymbolIdType				eSymbolId;
		QVector<TradeDetailData*>	vecTradeDetailData;

	public:
		~TradeDetailBill();
		void Resize(int nSize);
		void Free();
	};

	class MsgTradeDetail : public SubscribeBase
	{
		MSGTYPE(tradeDetail);
	public:
		static Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	};

}


#endif // __TRADEDETAIL_H__

#ifndef __MSGMARKETDETAIL_H__
#define __MSGMARKETDETAIL_H__


#include "subscribebase.h"
#include "common/bidsdata.h"
#include "common/asksdata.h"
#include "common/tradesdata.h"

#include <QSharedPointer>

namespace HBAPI
{
	class HBAPI_EXPORT MarketDetailBill
	{
	public:
		SymbolIdType	eSymbolId;
		double			dPriceNew;					///���³ɽ���
		double			dPriceOpen;					///���24Сʱ����
		double			dPriceHigh;					///���24Сʱ���
		double			dPriceLow;					///���24Сʱ���
		double			dPriceLast;					///���24Сʱ����
		double			dPriceAverage;				///����
		double			dAmount;					///�ɽ���
		double			dTotalAmount;				///���24Сʱ�ɽ���
		double			dTotalVolume;				///���24Сʱ�ɽ���

		double			dUpdownVolume;				///�ǵ��������¼ۼ�ȥ���̼ۣ�ԭ����level�ֶ�
		double			dUpdownRatio;				///�ǵ������ǵ�������level�ȿ��̼ۣ�ԭ����amp�ֶ�
		double			dTurnVolume;				///���
		double			dTurnoverRate;				///����
		double			dCommissionRatio;			///ί�ȣ�(ί��������ί������)/(ί��������ί������)*100%
		double			dPoor;						///ί�ί��ί���Ĳ�ֵ����ί�
		double			dOuterDisc;					///���̣�����(������):��ָ�������۳ɽ��Ĺ�Ʊ����,�������������ļ۸�,������гɽ�;
		double			dInnerDisc;					///���̣�����(������):��ָ������۸�ɽ��Ĺ�Ʊ����,������������ļ۸�,������гɽ�;
		double			dVolumeRatio;

		QVector<BidsData>		vecBidsData;		///��
		QVector<AsksData>		vecAsksData;		///����
		QVector<TradesData>		vecTradesData;		///�ɽ���

// 		double			dLevel;
// 		double			dAmp;

	};

	class HBAPI_EXPORT MsgMarketDetail : public SubscribeBase
	{
		Q_OBJECT
		MSGTYPE(marketDetail);
	public:
		static Subscriber GetSubscriber(SymbolIdType eSymbolId, PushType ePushType);

		virtual bool ReceiveJson(const QJsonObject& joPayload) override;

	protected:

	signals:
		void signal_Receive(const QSharedPointer<MarketDetailBill>& ptMarketDetailBill);

	};

}


#endif // __MSGMARKETDETAIL_H__

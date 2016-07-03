#ifndef __RESTORDERINFO_H__
#define __RESTORDERINFO_H__

#include "restrequestbase.h"

namespace HBAPI
{
	class HBAPI_EXPORT OrderInfo
	{
	public:
		int			nId;					 ///ί�ж���id
		OrderType	eType;					 ///ί�ж�������
		double		dOrderPrice;			 ///ί�м۸�
		double		dOrderAmount;			 ///ί������(�м��򵥣�����������)
		double		dProcessedPrice;		 ///�ɽ�ƽ���۸�
		double		dProcessedAmount;		 ///�Ѿ���ɵ�����(�м��򵥣�����ɽ����)
		double		dVot;					 ///���׶�
		double		dFee;					 ///������
		double		dTotal;					 ///�ܽ��׶ֻ������ҽ����г��Ż᷵�أ�
		OrderStatus	eStatus;				 ///״̬
	};

	///��ȡί������ 
	class HBAPI_EXPORT RestOrderInfo : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(order_info);
	public:
		void SendRequest(CoinType eCoinType, unsigned int uOrderId, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json, int nCode) override;

	signals:
		void signal_Receive(const QSharedPointer<OrderInfo>& ptOrderInfo);
	};

}

#endif // __RESTORDERINFO_H__

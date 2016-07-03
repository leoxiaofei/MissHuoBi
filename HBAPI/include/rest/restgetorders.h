#ifndef __RESTGETORDERS_H__
#define __RESTGETORDERS_H__

#include "restrequestbase.h"

#include <QDateTime>

namespace HBAPI
{
	class HBAPI_EXPORT OrdersData
	{
	public:
		int			nId;					///ί�ж���id
		OrderType	eType;					///ί�ж�������
		double		dOrderPrice;			///ί�м۸�
		double		dOrderAmount;			///ί������(�м��򵥣�����������)
		double		dProcessedAmount;		///�Ѿ���ɵ�����(�м��򵥣�����ɽ����)
		QDateTime	dtOrderTime;			///ί��ʱ��
	};

	///��ȡ�������ڽ��е�ί�� 
	class HBAPI_EXPORT RestGetOrders : public RestRequestBase
	{
		Q_OBJECT
		RESTTYPE(get_orders);
	public:
		void SendRequest(CoinType eCoinType, MarketType eMarketType = MT_CNY);

		virtual bool ReceiveJson(const QJsonDocument& json, int nCode) override;

	signals:
		void signal_Receive(const QList<OrdersData>& listOrdersData);

	};


}
#endif // __RESTGETORDERS_H__

#ifndef AUTOTRADE_H
#define AUTOTRADE_H

#include <QObject>
#include <functional>

namespace HBAPI
{
	class AccountInfoData;
	class TradeResult;
	class OrderInfo;
}

class StatTradeData;

typedef std::function<double(const double&)> PriceTaker;

class AutoTrade : public QObject
{
	Q_OBJECT
	Q_PROPERTY(bool running READ IsRunning WRITE SetRunning USER true)
public:
	AutoTrade(QObject* parent = 0);
	~AutoTrade();

	bool IsRunning();
	void SetRunning(bool bRunning);

	void Init();

	void SetPriceTaker(const PriceTaker& ptBuy, const PriceTaker& ptSell);

protected:
	void InitStateMachine();

public slots:
	void slot_UpdateAccountInfo(const QSharedPointer<
		HBAPI::AccountInfoData>& ptAccountInfoData);

	void slot_StatTradeData(const QSharedPointer<
		StatTradeData>& ptStatTradeData);

	void slot_TradeResult(const QSharedPointer<
		HBAPI::TradeResult>& ptTradeResult);

	void slot_OrderInfo(const QSharedPointer<HBAPI::OrderInfo>& ptOrderInfo);

	void slot_Buy();
	void slot_Sell();

	void slot_Judge();
	void slot_CheckResult();
	void slot_CancelOrder();

signals:
	void signal_WaitBuy();
	void signal_WaitSell();
	void signal_Buy();
	void signal_Sell();
	void signal_Checkout();					///下单
	void signal_OrderFinish();				///订单完成
	void signal_RetryCountExceeded();		///超出重试次数

private:
	class Impl;
	QScopedPointer<Impl> m_pImpl;
};

#endif // AUTOTRADE_H

#ifndef AUTOTRADE_H
#define AUTOTRADE_H

#include <QObject>
#include <functional>

namespace HBAPI
{
	class AccountInfoData;
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
	void slot_GetAccountInfo();
	void slot_UpdateAccountInfo(const QSharedPointer<
		HBAPI::AccountInfoData>& ptAccountInfoData);

	void slot_StatTradeData(const QSharedPointer<
		StatTradeData>& ptStatTradeData);

	void slot_Buy();
	void slot_Sell();

private:
	class Impl;
	QScopedPointer<Impl> m_pImpl;
};

#endif // AUTOTRADE_H

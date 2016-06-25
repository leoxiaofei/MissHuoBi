#ifndef __TRADESTATISTIC_H__
#define __TRADESTATISTIC_H__


#include "singletemplate.hpp"

#include <QObject>
#include <QVector>

namespace HBAPI
{
	class TradeDetailBill;
	class TradeDetailData;
}

class StatTradeData;
class TradeDetailModel;

class TradeStatistic : public QObject
{
	Q_OBJECT
public:
	TradeStatistic(QObject* parent = 0);
	~TradeStatistic();

	TradeDetailModel* GetTradeDetailModel();

public slots:
	void slot_AddTradeDetai(const QSharedPointer<HBAPI::TradeDetailBill>& ptTradeDetailBill);

protected:
	void Init();
	void StatTrade(const QVector<HBAPI::TradeDetailData*>& vecTrade);

signals:
	void signal_StatTradeData(const QSharedPointer<StatTradeData>& ptStatTradeData);

private:
	class Impl;
	QScopedPointer<Impl> m_pImpl;
};

typedef SingleTemplate<TradeStatistic> STS;

#endif // __TRADESTATISTIC_H__

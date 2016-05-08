#ifndef __TRADEDETAILMODEL_H__
#define __TRADEDETAILMODEL_H__

#include <QAbstractTableModel>
#include <QSharedPointer>

namespace HBAPI
{
	class TradeDetailBill;
	class TradeDetailData;
}

class StatTradeData;

class TradeDetailModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	TradeDetailModel(QObject* parent = 0);
	~TradeDetailModel();

	enum ColumnType {
		TD_TRADEID,
		TD_TIME,
		TD_PRICE,
		TD_AMOUNT,
		TD_DIRECTION,
		_TD_TOTOAL,
	};

	void RetranslateUi();

public:
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

protected:
	void GetDisplayRole(const QModelIndex &index, QVariant& val) const;

	void StatTrade(const QVector<HBAPI::TradeDetailData*>& vecTrade);
	void LastTradeRadio();

public slots:
	void slot_AddTradeDetai(const QSharedPointer<HBAPI::TradeDetailBill>& ptTradeDetailBill);

signals:
	void signal_StatTradeData(const QSharedPointer<StatTradeData>& ptStatTradeData);

private:
	class Impl;
	QScopedPointer<Impl> m_pImpl;
};


#endif // __TRADEDETAILMODEL_H__

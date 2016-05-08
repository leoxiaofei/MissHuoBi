#ifndef __MARKETDEPTHMANAGER_H__
#define __MARKETDEPTHMANAGER_H__

#include <QAbstractTableModel>
#include <QSharedPointer>

namespace HBAPI
{
	class MarketDepthData;
	class MarketDepthDiffData;

	class MarketDepthTopData;
	class MarketDepthTopDiffData;
}

class MarketDepthModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	MarketDepthModel(QObject* parent);
	~MarketDepthModel();

	enum ColumnType {
		MD_D,
		MD_PRICE,
		MD_AMOUNT,
		MD_TOTAL,
		_MD_TOTAL_
	};

	void RetranslateUi();

public:
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

public:
	double GetBuyPrice(const double& dTotalA) const;
	double GetSellPrice(const double& dTotalA) const;

public slots:
	void slot_ReciMarketDepthData(
		const QSharedPointer<HBAPI::MarketDepthData>& ptMarketDepthData);

	void slot_ReciMarketDepthDiffData(
		const QSharedPointer<HBAPI::MarketDepthDiffData>& ptMarketDepthDiffData);

	void slot_ReciMarketDepthTopData(
		const QSharedPointer<HBAPI::MarketDepthTopData>& ptMarketDepthData);

	void slot_ReciMarketDepthTopDiffData(
		const QSharedPointer<HBAPI::MarketDepthTopDiffData>& ptMarketDepthDiffData);

signals:
	void signal_ReloadMarketDepth();
	void signal_ReloadMarketDepthTop();

protected:
	void GetDisplayRole(const QModelIndex &index, QVariant& val) const;

private:
	class Impl;
	QScopedPointer<Impl> m_pImpl;
};


#endif // __MARKETDEPTHMANAGER_H__

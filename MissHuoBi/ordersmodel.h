#ifndef __ORDERSMODEL_H__
#define __ORDERSMODEL_H__

#include <QAbstractTableModel>

namespace HBAPI
{
	class OrdersData;
}

class OrdersModel : public QAbstractTableModel
{
public:
	OrdersModel(QObject *parent = 0);
	~OrdersModel();

	enum ColumnType {
		CT_ID,
		CT_TYPE,
		CT_ORDER_TIME,
		CT_ORDER_AMOUNT,
		CT_ORDER_PRICE,
		CT_PROCESSED_AMOUNT,
		_CT_TOTAL_
	};

	void SetDataSrc(const QList<HBAPI::OrdersData>& listOrdersData);

	void RetranslateUi();

	int GetOrderId(const QModelIndex& index) const;

public:
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	virtual QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const override;
private:
	class Impl;
	QScopedPointer<Impl> m_pImpl;
};


#endif // __ORDERSMODEL_H__

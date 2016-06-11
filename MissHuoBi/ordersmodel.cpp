#include "ordersmodel.h" 
#include "rest\restgetorders.h"

namespace
{

	const char* szColumnType[OrdersModel::_CT_TOTAL_] =
	{
		"id",
		"type",
		"order_time",
		"order_amount",
		"order_price",
		"processed_amount",
	};


}

class OrdersModel::Impl
{
public:
	QList<HBAPI::OrdersData> listOrdersData;
	QStringList listHeader;
};

OrdersModel::OrdersModel(QObject *parent)
	: QAbstractTableModel(parent)
	, m_pImpl(new Impl)
{
	RetranslateUi();
}

OrdersModel::~OrdersModel()
{
}

void OrdersModel::SetDataSrc(const QList<HBAPI::OrdersData>& listOrdersData)
{
	beginResetModel();

	m_pImpl->listOrdersData = listOrdersData;

	endResetModel();
}

int OrdersModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return parent.isValid() ? 0 : m_pImpl->listOrdersData.size();
}

int OrdersModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return parent.isValid() ? 0 : m_pImpl->listHeader.size();
}

QVariant OrdersModel::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
	QVariant varRet;

	if (role == Qt::DisplayRole)
	{
		const HBAPI::OrdersData& od = m_pImpl->listOrdersData[index.row()];
		switch (index.column())
		{
		case CT_ID:
			varRet = od.nId;
			break;
		case CT_TYPE:
			varRet = od.eType;
			break;
		case CT_ORDER_TIME:
			varRet = od.dtOrderTime;
			break;
		case CT_ORDER_AMOUNT:
			varRet = od.dOrderAmount;
			break;
		case CT_ORDER_PRICE:
			varRet = od.dOrderPrice;
			break;
		case CT_PROCESSED_AMOUNT:
			varRet = od.dProcessedAmount;
			break;
		default:
			break;
		}
	}

	return varRet;
}

void OrdersModel::RetranslateUi()
{
	m_pImpl->listHeader.clear();

	for (int ix = CT_ID; ix != _CT_TOTAL_; ++ix)
	{
		m_pImpl->listHeader.append(tr(szColumnType[ix]));
	}

	emit headerDataChanged(Qt::Horizontal, 0, m_pImpl->listHeader.size() - 1);

}

QVariant OrdersModel::headerData(int section, 
	Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	QVariant var;
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		var = m_pImpl->listHeader[section];
	}
	else
	{
		var = QAbstractTableModel::headerData(section, orientation, role);
	}

	return var;
}

int OrdersModel::GetOrderId(const QModelIndex& index) const
{
	return m_pImpl->listOrdersData[index.row()].nId;
}


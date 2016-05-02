#include "tradedetailmodel.h"
#include "msg\msgtradedetail.h"
#include "common\misshbtext.h"

#include <QQueue>
#include <QDateTime>
#include <QVariant>
#include <QDebug>

namespace
{
	const char* szColumnType[] = {
		QT_TRANSLATE_NOOP("TradeDetailModel", "TradeId"),
		QT_TRANSLATE_NOOP("TradeDetailModel", "Time"),
		QT_TRANSLATE_NOOP("TradeDetailModel", "Price"),
		QT_TRANSLATE_NOOP("TradeDetailModel", "Amount"),
		QT_TRANSLATE_NOOP("TradeDetailModel", "Direction"),
	};

}

class TradeDetailModel::Impl
{
public:
	QStringList listHeader;
	QList<HBAPI::TradeDetailData*> queTDData;
	int nMaxCount;
};

TradeDetailModel::TradeDetailModel(QObject* parent /*= 0*/)
: QAbstractTableModel(parent)
, m_pImpl(new Impl)
{
	m_pImpl->nMaxCount = 3000;
	RetranslateUi();
}

TradeDetailModel::~TradeDetailModel()
{

}

int TradeDetailModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return m_pImpl->queTDData.size();
}

int TradeDetailModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return m_pImpl->listHeader.size();
}

QVariant TradeDetailModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	QVariant vaRet;

	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		vaRet = m_pImpl->listHeader[section];
	}
	else
	{
		vaRet = QAbstractTableModel::headerData(section, orientation, role);
	}

	return vaRet;
}

void TradeDetailModel::GetDisplayRole(const QModelIndex &index, QVariant& val) const
{
	int nRow = index.row();
	HBAPI::TradeDetailData* tDData = m_pImpl->queTDData[nRow];

	switch (index.column())
	{
	case TD_TRADEID:
		val = tDData->nTradeId;
		break;
	case TD_TIME:
		val = QDateTime::fromTime_t(tDData->tTime).toString("yyyy-MM-dd hh:mm:ss");
		break;
	case TD_PRICE:
		val = tDData->dPrice;
		break;
	case TD_AMOUNT:
		val = tDData->dAmount;
		break;
	case TD_DIRECTION:
		if (tDData->eDirection < 3)
		{
			val = HBAPI::TrDirectionType(tDData->eDirection);
		}
		else
		{
			qDebug() << tDData->eDirection;
		}
		break;
	default:
		break;
	}
}

QVariant TradeDetailModel::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
	QVariant vaRet;
	switch (role)
	{
	case Qt::DisplayRole:
		GetDisplayRole(index, vaRet);
		break;
	default:
		break;
	}
	return vaRet;
}

void TradeDetailModel::slot_AddTradeDetai(const QSharedPointer<HBAPI::TradeDetailBill>& ptTradeDetailBill)
{
	if (!ptTradeDetailBill->vecTradeDetailData.isEmpty())
	{
		int nFirst = 0;
		//beginInsertRows(QModelIndex(), nFirst, nFirst + ptTradeDetailBill->vecTradeDetailData.size() - 1);
		beginInsertRows(QModelIndex(), nFirst, nFirst + ptTradeDetailBill->vecTradeDetailData.size() - 1);

		for (QVector<HBAPI::TradeDetailData*>::const_reverse_iterator itor
			= ptTradeDetailBill->vecTradeDetailData.crbegin();
			itor != ptTradeDetailBill->vecTradeDetailData.crend(); ++itor)
		{
			m_pImpl->queTDData.prepend(*itor);
		}

		endInsertRows();

		ptTradeDetailBill->vecTradeDetailData.clear();

		int nRemove = m_pImpl->queTDData.size() - m_pImpl->nMaxCount;
		if (nRemove > 0)
		{
			beginRemoveRows(QModelIndex(), 0, nRemove - 1);

			while (nRemove)
			{
				ptTradeDetailBill->vecTradeDetailData.append(m_pImpl->queTDData.takeLast());
				--nRemove;
			}

			endRemoveRows();
		}
	}
}

void TradeDetailModel::RetranslateUi()
{
	m_pImpl->listHeader.clear();

	for (int ix = TD_TRADEID; ix != _TD_TOTOAL; ++ix)
	{
		m_pImpl->listHeader.append(tr(szColumnType[ix]));
	}

	emit headerDataChanged(Qt::Horizontal, 0, m_pImpl->listHeader.size() - 1);
}

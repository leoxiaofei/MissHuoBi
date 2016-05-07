#include "tradedetailmodel.h"
#include "msg\msgtradedetail.h"
#include "common\misshbtext.h"

#include <QQueue>
#include <QDateTime>
#include <QVariant>
#include <QDebug>
#include <algorithm>

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
	int nRow = m_pImpl->queTDData.size() - index.row() - 1;
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
		val = QString::number(tDData->dPrice, 'f', 2);
		break;
	case TD_AMOUNT:
		val = QString::number(tDData->dAmount, 'f', 4);
		break;
	case TD_DIRECTION:
		val = HBAPI::TrDirectionType(tDData->eDirection);
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

		for (QVector<HBAPI::TradeDetailData*>::const_iterator itor
			= ptTradeDetailBill->vecTradeDetailData.cbegin();
			itor != ptTradeDetailBill->vecTradeDetailData.cend(); ++itor)
		{
			m_pImpl->queTDData.append(*itor);
		}

		endInsertRows();

		ptTradeDetailBill->vecTradeDetailData.clear();

		int nRemove = m_pImpl->queTDData.size() - m_pImpl->nMaxCount;
		if (nRemove > 0)
		{
			beginRemoveRows(QModelIndex(), 0, nRemove - 1);

			while (nRemove)
			{
				ptTradeDetailBill->vecTradeDetailData.append(m_pImpl->queTDData.takeFirst());
				--nRemove;
			}

			endRemoveRows();
		}
	}

	LastTradeRadio();
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

class LastLessThan
{
public:

	inline bool operator()(HBAPI::TradeDetailData*p, const time_t& t) const
	{
		return p->tTime < t;
	}

	inline bool operator()(const time_t& t, HBAPI::TradeDetailData* p) const
	{
		return t < p->tTime;
	}

};

void TradeDetailModel::LastTradeRadio()
{
	QList<HBAPI::TradeDetailData*>::const_iterator cFind = 
		std::lower_bound(m_pImpl->queTDData.constBegin(), m_pImpl->queTDData.constEnd(),
		QDateTime::currentDateTime().addSecs(-5).toTime_t(), LastLessThan());
	
// 	qDebug() << m_pImpl->queTDData.constEnd() - cFind <<":"<< QDateTime::fromTime_t((*cFind)->tTime).toString("hh:mm:ss") 
// 		<< " " << QDateTime::currentDateTime().secsTo(QDateTime::fromTime_t((*cFind)->tTime));

	double dA[2] = { 0 };
	double dS[2] = { 0 };

	for (QList<HBAPI::TradeDetailData*>::const_iterator citor = cFind;
		citor != m_pImpl->queTDData.constEnd(); ++citor)
	{
		HBAPI::TradeDetailData* pTrade = *citor;
		switch (pTrade->eDirection)
		{
		case HBAPI::DT_BUYING:
		case HBAPI::DT_BUYING2:
			dA[0] += pTrade->dAmount;
			++dS[0];
			break;
		case HBAPI::DT_SELLING:
		case HBAPI::DT_SELLIN2:
			dA[1] += pTrade->dAmount;
			++dS[1];
			break;
		default:
			break;
		}
	}

// 	qDebug() << "BUYING: " << dA[0] << ":" << dS[0] << "SELLING: " << dA[1] << ":" << dS[1];
	double dSpan = dA[0] - dA[1];
	qDebug() << dSpan << " " << dS[0] << ":" << dS[1];
}

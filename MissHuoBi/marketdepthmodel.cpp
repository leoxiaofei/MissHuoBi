#include "marketdepthmodel.h" 
#include "common\asksdata.h"
#include "common\bidsdata.h"
#include "common\marketdepthtopdata.h"
#include "common\marketdepthdata.h"

#include <QDebug>

using HBAPI::AskDepthData;
using HBAPI::BidDepthData;

namespace
{
	template<class DD, class D>
	void ConvData(const D& d, DD& dd)
	{
		dd.dPrice = d.dPrice;			///�۸�
		dd.dAmount = d.dAmount;			///�ɽ���
	}

	template<class I, class D, class U, class DD>
	void UpdateDD(const QVector<I>& vecInsert, const QVector<D>& vecDelete, 
		const QVector<U>& vecUpdate, QList<DD>& listDD)
	{
		DD add;

		for (QVector<D>::const_iterator citor = vecDelete.constBegin();
			citor != vecDelete.constEnd(); ++citor)
		{
			listDD.removeAt(citor->nRow);
		}

		for (int ix = vecInsert.size() - 1; ix >= 0; --ix)
		{
			const I& i = vecInsert[ix];
			ConvData(i, add);
			listDD.insert(i.nRow, add);
		}

		for (QVector<U>::const_iterator citor = vecUpdate.constBegin();
			citor != vecUpdate.constEnd(); ++citor)
		{
			ConvData(*citor, add);
			listDD[citor->nRow] = add;
		}

		double dTotal(0);
		for (QList<DD>::iterator itor = listDD.begin();
			itor != listDD.end(); ++itor)
		{
			dTotal += itor->dAmount;
			itor->dTotal = dTotal;
		}
	}

	template<class T>
	QString OutList(const QList<T>& listOut)
	{
		QString strRet;

		foreach(const T& t, listOut)
		{
			strRet += QString::number(t.dPrice, 'f', 2);
			strRet += "\r\n";
		}

		return strRet;
	}

	const char* szColumnType[] = {
		QT_TRANSLATE_NOOP("MarketDepthModel", "D"),
		QT_TRANSLATE_NOOP("MarketDepthModel", "Price"),
		QT_TRANSLATE_NOOP("MarketDepthModel", "Amount"),
		QT_TRANSLATE_NOOP("MarketDepthModel", "Total")
	};
}

class MarketDepthModel::Impl
{
public:
	quint64					uVersion;
	QList<AskDepthData>		listAskDepthData;
	QList<BidDepthData>		listBidDepthData;

	QStringList listHeader;
};

MarketDepthModel::MarketDepthModel(QObject* parent)
: QAbstractTableModel(parent)
, m_pImpl(new Impl)
{
	RetranslateUi();
}

MarketDepthModel::~MarketDepthModel()
{
}

void MarketDepthModel::slot_ReciMarketDepthData(
	const QSharedPointer<HBAPI::MarketDepthData>& ptMarketDepthData)
{
	if (m_pImpl->uVersion != ptMarketDepthData->uVersion)
	{
		beginResetModel();
		m_pImpl->uVersion = ptMarketDepthData->uVersion;
		m_pImpl->listAskDepthData = ptMarketDepthData->listAskDepthData;
		m_pImpl->listBidDepthData = ptMarketDepthData->listBidDepthData;
		endResetModel();
	}
	else
	{
		///У������
		if (m_pImpl->listAskDepthData != ptMarketDepthData->listAskDepthData)
		{
			QString s1, s2;

			s1 = OutList(m_pImpl->listAskDepthData);
			s2 = OutList(ptMarketDepthData->listAskDepthData);

			qDebug() << "AskDepthData Fail!";
		}

		if (m_pImpl->listBidDepthData != ptMarketDepthData->listBidDepthData)
		{
			qDebug() << "BidDepthData Fail!";
		}
	}
}

void MarketDepthModel::slot_ReciMarketDepthDiffData(
	const QSharedPointer<HBAPI::MarketDepthDiffData>& ptMarketDepthDiffData)
{
	if (m_pImpl->uVersion == ptMarketDepthDiffData->uVersionOld)
	{
		///���µ�ǰ�����¼
		m_pImpl->uVersion = ptMarketDepthDiffData->uVersion;

		int nAskSpan = ptMarketDepthDiffData->vecAskInsertData.size()
			- ptMarketDepthDiffData->vecAskDeleteData.size();

		if (nAskSpan > 0)
		{
			int nFirst = m_pImpl->listAskDepthData.size();
			beginInsertRows(QModelIndex(), nFirst, nFirst + nAskSpan - 1);
		}
		else if (nAskSpan < 0)
		{
			int nFirst = m_pImpl->listAskDepthData.size() + nAskSpan;
			beginRemoveRows(QModelIndex(), nFirst, m_pImpl->listAskDepthData.size() - 1);
		}

		UpdateDD(ptMarketDepthDiffData->vecAskInsertData,
			ptMarketDepthDiffData->vecAskDeleteData,
			ptMarketDepthDiffData->vecAskUpdateData,
			m_pImpl->listAskDepthData);

		qDebug() << "Ask Insert: " << ptMarketDepthDiffData->vecAskInsertData.size()
			<< "Ask Delete: " << ptMarketDepthDiffData->vecAskDeleteData.size()
			<< "Ask Update:" << ptMarketDepthDiffData->vecAskUpdateData.size();

		if (nAskSpan > 0)
		{
			endInsertRows();
		}
		else if (nAskSpan < 0)
		{
			endRemoveRows();
		}
		else
		{
			emit dataChanged(index(0, MD_PRICE), index(m_pImpl->listAskDepthData.size() - 1, MD_TOTAL));
		}

		int nBidSpan = ptMarketDepthDiffData->vecBidInsertData.size()
			- ptMarketDepthDiffData->vecBidDeleteData.size();

		if (nBidSpan > 0)
		{
			int nFirst = m_pImpl->listBidDepthData.size() + m_pImpl->listAskDepthData.size();
			beginInsertRows(QModelIndex(), nFirst, nFirst + nBidSpan - 1);
		}
		else if (nBidSpan < 0)
		{
			int nFirst = m_pImpl->listBidDepthData.size() + m_pImpl->listAskDepthData.size() + nBidSpan;
			beginRemoveRows(QModelIndex(), nFirst, m_pImpl->listBidDepthData.size() - 1);
		}

		UpdateDD(ptMarketDepthDiffData->vecBidInsertData,
			ptMarketDepthDiffData->vecBidDeleteData,
			ptMarketDepthDiffData->vecBidUpdateData,
			m_pImpl->listBidDepthData);

		qDebug() << "Bid Insert: " << ptMarketDepthDiffData->vecBidInsertData.size()
			<< "Bid Delete: " << ptMarketDepthDiffData->vecBidDeleteData.size()
			<< "Bid Update:" << ptMarketDepthDiffData->vecBidUpdateData.size();

		if (nBidSpan > 0)
		{
			endInsertRows();
		}
		else if (nBidSpan < 0)
		{
			endRemoveRows();
		}
		else
		{
			emit dataChanged(index(m_pImpl->listAskDepthData.size(), MD_PRICE), 
				index(m_pImpl->listAskDepthData.size() + m_pImpl->listBidDepthData.size() - 1, MD_TOTAL));
		}
	}
	else
	{
		///���»�ȡ�������
		emit signal_ReloadMarketDepth();
	}
}

void MarketDepthModel::slot_ReciMarketDepthTopData(
	const QSharedPointer<HBAPI::MarketDepthTopData>& ptMarketDepthData)
{
	if (m_pImpl->uVersion != ptMarketDepthData->uVersion)
	{
		beginResetModel();
		m_pImpl->uVersion = ptMarketDepthData->uVersion;
		m_pImpl->listAskDepthData = ptMarketDepthData->listAskDepthData;
		m_pImpl->listBidDepthData = ptMarketDepthData->listBidDepthData;
		endResetModel();
	}
	else
	{
		///У������
		if (m_pImpl->listAskDepthData != ptMarketDepthData->listAskDepthData)
		{
			QString s1, s2;

			s1 = OutList(m_pImpl->listAskDepthData);
			s2 = OutList(ptMarketDepthData->listAskDepthData);

			qDebug() << "AskDepthData Fail!";
		}

		if (m_pImpl->listBidDepthData != ptMarketDepthData->listBidDepthData)
		{
			qDebug() << "BidDepthData Fail!";
		}
	}
}

void MarketDepthModel::slot_ReciMarketDepthTopDiffData(
	const QSharedPointer<HBAPI::MarketDepthTopDiffData>& ptMarketDepthDiffData)
{
	if (m_pImpl->uVersion == ptMarketDepthDiffData->uVersionOld)
	{
		///���µ�ǰ�����¼
		m_pImpl->uVersion = ptMarketDepthDiffData->uVersion;

		int nAskSpan = ptMarketDepthDiffData->vecAskInsertData.size()
			- ptMarketDepthDiffData->vecAskDeleteData.size();

		if (nAskSpan > 0)
		{
			int nFirst = m_pImpl->listAskDepthData.size();
			beginInsertRows(QModelIndex(), nFirst, nFirst + nAskSpan - 1);
		}
		else if (nAskSpan < 0)
		{
			int nFirst = m_pImpl->listAskDepthData.size() + nAskSpan;
			beginRemoveRows(QModelIndex(), nFirst, m_pImpl->listAskDepthData.size() - 1);
		}

		UpdateDD(ptMarketDepthDiffData->vecAskInsertData,
			ptMarketDepthDiffData->vecAskDeleteData,
			ptMarketDepthDiffData->vecAskUpdateData,
			m_pImpl->listAskDepthData);

		if (nAskSpan > 0)
		{
			endInsertRows();
		}
		else if (nAskSpan < 0)
		{
			endRemoveRows();
		}
		else
		{
			emit dataChanged(index(0, MD_PRICE), index(m_pImpl->listAskDepthData.size() - 1, MD_TOTAL));
		}

		int nBidSpan = ptMarketDepthDiffData->vecBidInsertData.size()
			- ptMarketDepthDiffData->vecBidDeleteData.size();

		if (nBidSpan > 0)
		{
			int nFirst = m_pImpl->listBidDepthData.size();
			beginInsertRows(QModelIndex(), nFirst, nFirst + nBidSpan - 1);
		}
		else if (nBidSpan < 0)
		{
			int nFirst = m_pImpl->listBidDepthData.size() + nBidSpan;
			beginRemoveRows(QModelIndex(), nFirst, m_pImpl->listBidDepthData.size() - 1);
		}

		UpdateDD(ptMarketDepthDiffData->vecBidInsertData,
			ptMarketDepthDiffData->vecBidDeleteData,
			ptMarketDepthDiffData->vecBidUpdateData,
			m_pImpl->listBidDepthData);

		if (nBidSpan > 0)
		{
			endInsertRows();
		}
		else if (nBidSpan < 0)
		{
			endRemoveRows();
		}
		else
		{
			emit dataChanged(index(m_pImpl->listAskDepthData.size(), MD_PRICE),
				index(m_pImpl->listAskDepthData.size() + m_pImpl->listBidDepthData.size() - 1, MD_TOTAL));
		}
	}
	else
	{
		///���»�ȡ�������
		emit signal_ReloadMarketDepthTop();
	}
}

int MarketDepthModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return m_pImpl->listAskDepthData.size() + m_pImpl->listBidDepthData.size();
}

int MarketDepthModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return m_pImpl->listHeader.size();
}

QVariant MarketDepthModel::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
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

void MarketDepthModel::GetDisplayRole(const QModelIndex &index, QVariant& val) const
{
	int nRow = index.row();

	switch (index.column())
	{
	case MD_D:
		val = nRow < m_pImpl->listAskDepthData.size() ? "A" : "B";
		break;
	case MD_PRICE:
		val = nRow < m_pImpl->listAskDepthData.size()
			? m_pImpl->listAskDepthData[nRow].dPrice
			: m_pImpl->listBidDepthData[nRow - m_pImpl->listAskDepthData.size()].dPrice;
		break;
	case MD_AMOUNT:
		val = nRow < m_pImpl->listAskDepthData.size()
			? m_pImpl->listAskDepthData[nRow].dAmount
			: m_pImpl->listBidDepthData[nRow - m_pImpl->listAskDepthData.size()].dAmount;
		break;
	case MD_TOTAL:
		val = nRow < m_pImpl->listAskDepthData.size()
			? m_pImpl->listAskDepthData[nRow].dTotal
			: m_pImpl->listBidDepthData[nRow - m_pImpl->listAskDepthData.size()].dTotal;
		break;
	default:
		break;
	}
}

QVariant MarketDepthModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
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

void MarketDepthModel::RetranslateUi()
{
	m_pImpl->listHeader.clear();

	for (int ix = MD_D; ix != _MD_TOTAL_; ++ix)
	{
		m_pImpl->listHeader.append(tr(szColumnType[ix]));
	}

	emit headerDataChanged(Qt::Horizontal, 0, m_pImpl->listHeader.size() - 1);
}
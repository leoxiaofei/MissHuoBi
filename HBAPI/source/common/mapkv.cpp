#include "common\mapkv.h"
#include <QUrlQuery>


namespace HBAPI
{
	void MapKV::insert(const QString& strKey, int nValue)
	{
		listData.append(qMakePair(strKey, QString::number(nValue)));
	}
	
	void MapKV::insert(const QString& strKey, unsigned int uValue)
	{
		listData.append(qMakePair(strKey, QString::number(uValue)));
	}

	void MapKV::insert(const QString& strKey, const double& dValue)
	{
		listData.append(qMakePair(strKey, QString::number(dValue)));
	}

	void MapKV::insert(const QString& strKey, const QString& strValue)
	{
		listData.append(qMakePair(strKey, strValue));
	}

	void MapKV::remove(const QString& strKey)
	{
		for (QList<QPair<QString, QString> >::iterator itor = listData.begin();
			itor != listData.end(); ++itor)
		{
			if (itor->first == strKey)
			{
				itor = listData.erase(itor);
				break;
			}
		}
	}

	void MapKV::sort()
	{
		qSort(listData.begin(), listData.end());
	}

	QByteArray MapKV::toUrlEncode() const
	{
		QUrlQuery uq;
		uq.setQueryItems(listData);
		return uq.toString().toUtf8();
	}

	MapKV& MapKV::operator+=(MapKV& other)
	{
		listData.append(other.listData);

		return *this;
	}

}

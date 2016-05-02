#ifndef __MAPKV_H__
#define __MAPKV_H__

#include <QList>
#include <QPair>
#include <QString>


namespace HBAPI
{

	class MapKV
	{
	public:
		void insert(const QString& strKey, int nValue);
		void insert(const QString& strKey, unsigned int uValue);
		void insert(const QString& strKey, const double& dValue);
		void insert(const QString& strKey, const QString& strValue);
		void remove(const QString& strKey);

		void sort();

		QByteArray toUrlEncode() const;

		MapKV& operator += (MapKV& other);

	protected:

	public:
		QList<QPair<QString, QString> > listData;
	};

}

#endif // __MAPKV_H__

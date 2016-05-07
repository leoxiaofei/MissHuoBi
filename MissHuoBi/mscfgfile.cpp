#include "mscfgfile.h"

#include <QFile>
#include <QByteArray>
#include <QDataStream>

bool MsCfgFile::LoadFile(const QString& strFile)
{
	bool bRet(false);
	QFile file(strFile);
	if (file.open(QFile::ReadOnly))
	{
		QByteArray ba = qUncompress(file.readAll());

		ba = QByteArray::fromBase64(ba);

		QDataStream in(&ba, QIODevice::ReadOnly);

		in >> strWebSocketUrl
			>> strRestUrl
			>> strAccessKey
			>> strSecretKey;

		bRet = true;
	}

	return bRet;
}

bool MsCfgFile::SaveFile(const QString& strFile)
{
	bool bRet(false);
	QByteArray ba;
	
	{
		QDataStream out(&ba, QIODevice::WriteOnly);
		out << strWebSocketUrl
			<< strRestUrl
			<< strAccessKey
			<< strSecretKey;
	}

	ba = ba.toBase64();

	ba = qCompress(ba, 7);

	QFile file(strFile);
	if (file.open(QFile::WriteOnly | QFile::Truncate))
	{
		bRet = ba.size() == file.write(ba);
	}

	return bRet;
}


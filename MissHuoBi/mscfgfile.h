#ifndef __MSCONFIG_H__
#define __MSCONFIG_H__

#include <QString>

class MsCfgFile
{
public:
	QString strWebSocketUrl;
	QString strRestUrl;
	QString strAccessKey;
	QString strSecretKey;

public:
	bool LoadFile(const QString& strFile);
	bool SaveFile(const QString& strFile);

};


#endif // __MSCONFIG_H__

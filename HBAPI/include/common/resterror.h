#ifndef __RESTERROR_H__
#define __RESTERROR_H__

#include "hbglobal.h"


#include <QString>

class QJsonDocument;

namespace HBAPI
{
	class HBAPI_EXPORT RestError
	{
	public:
		int		nCode;
		QString strMessage;
	};

	bool CheckError(const QJsonDocument& json);
	bool ParseRestError(const QJsonDocument& json, RestError& rError);
}




#endif // __RESTERROR_H__

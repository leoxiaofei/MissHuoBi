#include "common\resterror.h"

#include <QJsonDocument>
#include <QJsonObject>

namespace HBAPI
{

namespace
{
	enum ElemText { ET_MESSAGE, ET_CODE };

	QString szElemText[] =
	{
		"message",
		"code",
	};
}

bool CheckError(const QJsonDocument& json)
{
	return json.isObject() && json.object().contains(szElemText[ET_CODE]);
}

bool ParseRestError(const QJsonDocument& json, RestError& rError)
{
	QJsonObject obj = json.object();

	rError.nCode = obj[szElemText[ET_CODE]].toInt();
	rError.strMessage = obj[szElemText[ET_MESSAGE]].toString();

	return true;
}

}

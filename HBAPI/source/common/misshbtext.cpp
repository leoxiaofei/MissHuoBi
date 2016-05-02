#include "common\misshbtext.h"

#include <QCoreApplication>

namespace HBAPI
{
	const char* DirectionTypeText[] =
	{
		"",
		QT_TRANSLATE_NOOP("HBAPI", "BUYING"),
		QT_TRANSLATE_NOOP("HBAPI", "SELLING"),
	};

	QString TrDirectionType(DirectionType eType)
	{
		return qApp->translate("HBAPI", DirectionTypeText[eType]);
	}

}

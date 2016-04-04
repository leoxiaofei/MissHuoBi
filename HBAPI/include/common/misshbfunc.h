#ifndef __MISSHBFUNC_H__
#define __MISSHBFUNC_H__

#include "misshbdef.h"

class QString;
class QJsonValue;

namespace HBAPI
{
	SymbolIdType GetSymbolIdType(const QString& strSymbolId);
	PeriodType GetPeriodType(const QString& strPeriodType);
	PercentType GetPercentType(const QString& strPercentType);

}
#endif // __MISSHBFUNC_H__

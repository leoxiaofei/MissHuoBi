#ifndef __MISSHBFUNC_H__
#define __MISSHBFUNC_H__

#include "misshbdef.h"
#include <boost\rational.hpp>

class QString;
class QJsonValue;

namespace HBAPI
{
	SymbolIdType GetSymbolIdType(const QString& strSymbolId);

	boost::rational<int> GetRationalValue(const QJsonValue& jvPrice);


}
#endif // __MISSHBFUNC_H__

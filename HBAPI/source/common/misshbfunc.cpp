#include "common/misshbfunc.h"
#include <QString>
#include <QJsonValue>

namespace HBAPI
{
	SymbolIdType GetSymbolIdType(const QString& strSymbolId)
	{
		SymbolIdType e(SIT_BTCCNY);
		
		for (int ix = 0; szSymbolIdType[ix] != 0; ++ix)
		{
			if (szSymbolIdType[ix] == strSymbolId)
			{
				e = static_cast<SymbolIdType>(ix);
				break;
			}
		}

		return e;
	}

	HBAPI::PeriodType GetPeriodType(const QString& strPeriodType)
	{
		PeriodType e(PT_KLINETIMELINE);

		for (int ix = 0; szPeriodType[ix] != 0; ++ix)
		{
			if (szPeriodType[ix] == strPeriodType)
			{
				e = static_cast<PeriodType>(ix);
				break;
			}
		}

		return e;
	}

	HBAPI::PercentType GetPercentType(const QString& strPercentType)
	{
		PercentType e(PT_PERCENTTOP);

		for (int ix = 0; szPercentType[ix] != 0; ++ix)
		{
			if (szPercentType[ix] == strPercentType)
			{
				e = static_cast<PercentType>(ix);
				break;
			}
		}

		return e;
	}

	int qPow10[] = {
		1,
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
		10000000,
		100000000,
		1000000000,
	};

// 	boost::rational<int> GetRationalValue(const QJsonValue& jvPrice)
// 	{
// 		boost::rational<int> rRet;
// 		
// 		QString strPrice = QString::number(jvPrice.toDouble(), 'f', 6);
// 		int nIdx = strPrice.lastIndexOf('.');
// 		if (nIdx != -1)
// 		{
// 			strPrice.remove(nIdx, 1);
// 			nIdx = (strPrice.size() - nIdx);
// 		}
// 		else
// 		{
// 			nIdx = 0;
// 		}
// 		
// 		rRet.assign(strPrice.toInt(), qPow10[nIdx]);
// 
// 		return rRet;
// 	}

}
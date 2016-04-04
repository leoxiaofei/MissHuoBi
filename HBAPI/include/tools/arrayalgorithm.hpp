#ifndef ARRAYALGORITHM_H__
#define ARRAYALGORITHM_H__

#include <string>

namespace OPEUIEX
{
	template <class T>
	int IndexOf(T szSrc[], int nCount, const T& uValue)
	{
		int nRet(-1);

		for (int ix = 0; ix < nCount; ++ix)
		{
			if (szSrc[ix] == uValue)
			{
				nRet = ix;
				break;
			}
		}

		return nRet;
	}

	template <class T, class V>
	int IndexOf(T szSrc[], int nCount, const V& uValue)
	{
		int nRet(-1);

		for (int ix = 0; ix < nCount; ++ix)
		{
			if (szSrc[ix] == uValue)
			{
				nRet = ix;
				break;
			}
		}

		return nRet;
	}

	int IndexOf(const char* szSrc[], int nCount, const char* strValue)
	{
		int nRet(-1);
		if (strValue)
		{
			for (int ix = 0; ix < nCount; ++ix)
			{
				if (std::strcmp(szSrc[ix], strValue) == 0)
				{
					nRet = ix;
					break;
				}
			}
		}

		return nRet;
	}
}


#endif // ARRAYALGORITHM_H__

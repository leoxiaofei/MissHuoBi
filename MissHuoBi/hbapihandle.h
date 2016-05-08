#ifndef HBAPIHANDLE_H
#define HBAPIHANDLE_H

#include <QObject>
#include "singletemplate.hpp"

namespace HBAPI
{
	class HbMarket;
	class HbMarketLinker;
	class HbRest;
	class HbRestLinker;
}


class HBAPIHandle : public QObject
{
	Q_OBJECT

public:
	HBAPIHandle(QObject *parent = 0);
	~HBAPIHandle();

	inline HBAPI::HbMarket* GetMarket()
	{
		return pM;
	}

	inline HBAPI::HbMarketLinker* GetMarketLinker()
	{
		return pML;
	}

	inline HBAPI::HbRest* GetRest()
	{
		return pR;
	}

	inline HBAPI::HbRestLinker* GetRestLinker()
	{
		return pRL;
	}

protected:
	void Init();

private:
	HBAPI::HbMarket*			pM;
	HBAPI::HbMarketLinker*		pML;

	HBAPI::HbRest*				pR;
	HBAPI::HbRestLinker*		pRL;
};

typedef SingleTemplate<HBAPIHandle> SHBAPI;

#endif // HBAPIHANDLE_H

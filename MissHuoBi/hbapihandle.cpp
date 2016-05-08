#include "hbapihandle.h"
#include "mscfgfile.h"
#include "hbrestlinker.h"
#include "hbrest.h"
#include "hbmarket.h"
#include "hbmarketlinker.h"

#include <QUrl>

using namespace HBAPI;

HBAPIHandle::HBAPIHandle(QObject *parent)
	: QObject(parent)
{
	Init();
}

HBAPIHandle::~HBAPIHandle()
{

}

void HBAPIHandle::Init()
{
	MsCfgFile msCfg;
	msCfg.LoadFile("MsCfg.hb");

	pR = new HbRest(this);
	pRL = new HbRestLinker(this);
	pR->SetSendFunc(std::bind(&HbRestLinker::PostData, pRL, std::placeholders::_1));
	pRL->SetRecvFunc(std::bind(&HbRest::ParserRequest, pR, std::placeholders::_1, std::placeholders::_2));

	pR->SetKey(msCfg.strAccessKey, msCfg.strSecretKey);
	pRL->SetUrl(QUrl(msCfg.strRestUrl));

	pM = new HbMarket(this);
	pML = new HbMarketLinker(this);
	pM->SetSendFunc(pML->GetSendFunc());
	pML->SetRecvFunc(std::bind(&HbMarket::ParserRequest, pM, std::placeholders::_1),
		std::bind(&HbMarket::ParserMessage, pM, std::placeholders::_1));

	pML->SetUrl(QUrl(msCfg.strWebSocketUrl));


}


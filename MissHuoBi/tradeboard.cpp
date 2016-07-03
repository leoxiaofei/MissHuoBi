#include "tradeboard.h"
#include "tradedetailmodel.h"
#include "hbapihandle.h"
#include "msg\msgtradedetail.h"
#include "hbmarket.h"
#include "tradestatistic.h"

using namespace HBAPI;

TradeBoard::TradeBoard(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	Init();
}

TradeBoard::~TradeBoard()
{

}

void TradeBoard::Init()
{
	TradeDetailModel* pTradeModel = STS::Instance().GetTradeDetailModel();

	ui.tvTradeLog->setModel(pTradeModel);
	ui.tvTradeLog->hideColumn(TradeDetailModel::TD_TRADEID);
	ui.tvTradeLog->hideColumn(TradeDetailModel::TD_TIME);
	ui.tvTradeLog->horizontalHeader()->setSectionResizeMode(TradeDetailModel::TD_PRICE, QHeaderView::Stretch);
	ui.tvTradeLog->horizontalHeader()->setSectionResizeMode(TradeDetailModel::TD_AMOUNT, QHeaderView::Stretch);
	ui.tvTradeLog->horizontalHeader()->setSectionResizeMode(TradeDetailModel::TD_DIRECTION, QHeaderView::Stretch);
}

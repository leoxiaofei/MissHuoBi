#include "tradeboard.h"
#include "tradedetailmodel.h"
#include "hbapihandle.h"
#include "msg\msgtradedetail.h"
#include "hbmarket.h"

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
	TradeDetailModel* pTradeModel = new TradeDetailModel(ui.tvTradeLog);

	ui.tvTradeLog->setModel(pTradeModel);
	ui.tvTradeLog->hideColumn(TradeDetailModel::TD_TRADEID);
	ui.tvTradeLog->hideColumn(TradeDetailModel::TD_TIME);
	ui.tvTradeLog->horizontalHeader()->setSectionResizeMode(TradeDetailModel::TD_PRICE, QHeaderView::Stretch);
	ui.tvTradeLog->horizontalHeader()->setSectionResizeMode(TradeDetailModel::TD_AMOUNT, QHeaderView::Stretch);
	ui.tvTradeLog->horizontalHeader()->setSectionResizeMode(TradeDetailModel::TD_DIRECTION, QHeaderView::Stretch);

	MsgTradeDetail* pMsgTradeDetail = 
		SHBAPI::Instance().GetMarket()->QueryMessage<MsgTradeDetail>();

	QObject::connect(pMsgTradeDetail, &MsgTradeDetail::signal_Receive,
		pTradeModel, &TradeDetailModel::slot_AddTradeDetai);
}

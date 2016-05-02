#include "marketboard.h"
#include "marketdepthmodel.h"

#include <QSortFilterProxyModel>

class MarketBoard::Impl
{
public:

};

MarketBoard::MarketBoard(QWidget *parent)
	: QWidget(parent)
	, m_pImpl(new Impl)
{
	ui.setupUi(this);
}

MarketBoard::~MarketBoard()
{

}

void MarketBoard::Init(MarketDepthModel* pMarketDepthModel)
{
	QSortFilterProxyModel* pAskModel = new QSortFilterProxyModel(this);
	pAskModel->setSourceModel(pMarketDepthModel);
	pAskModel->setFilterFixedString("A");
	pAskModel->setFilterKeyColumn(MarketDepthModel::MD_D);
	ui.tvAsk->setModel(pAskModel);
	ui.tvAsk->hideColumn(MarketDepthModel::MD_D);

	QSortFilterProxyModel* pBidModel = new QSortFilterProxyModel(this);
	pBidModel->setSourceModel(pMarketDepthModel);
	pBidModel->setFilterFixedString("B");
	pBidModel->setFilterKeyColumn(MarketDepthModel::MD_D);
	ui.tvBid->setModel(pBidModel);
	ui.tvBid->hideColumn(MarketDepthModel::MD_D);
}

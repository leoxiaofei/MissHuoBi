#include "common/misshbdef.h"

namespace HBAPI
{
	const char* szAttributeName[] = {
		"symbolId",
		"pushType",
		"symbolList",
		"msgType",
		"requestIndex",
		"version",
		"retCode",
		"request",
		"_id",
		"idCur",
		"idPrev",
		"timeMax",
		"timeMin",
		"payload",

		"tradeId",
		"price",
		"time",
		"amount",
		"direction",
		"topBids",
		"topAsks",

		"level",
		"accuAmount",

		"priceNew",
		"priceOpen",
		"priceHigh",
		"priceLow",
		"priceLast",
		"totalAmount",
		"amp",
		"trades",
		"bids",
		"asks",
		"commissionRatio",
		"poor",
		"updownVolume",
		"updownRatio",
		"priceAverage",
		"volumeRatio",
		"turnVolume",
		"turnoverRate",
		"outerDisc",
		"innerDisc",
		"totalVolume",

		"period",
		"percent",

		"volume",
		"count",
		"row",

		"versionOld",
		"bidInsert",
		"bidDelete",
		"bidUpdate",
		"askInsert",
		"askDelete",
		"askUpdate",

		"priceAsk",
		"priceBid",

		"askPrice",
		"askAmount",
		"askTotal",

		"bidPrice",
		"bidAmount",
		"bidTotal",

		"from",
		"to",
	};

	const char* szSymbolIdType[] = {
		"btccny", 
		"ltccny", 
		"btcusd",
		0
	};


	const char* szPushType[] = {
		"pushLong",
		"pushShort",
		0
	};

	const char* szPeriodType[] = {
		"1min",                      // 1分钟k线
		"5min",                      // 5分钟k线
		"15min",                     // 15分钟k线
		"30min",                     // 30分钟k线
		"60min",                     // 60分钟k线
		"1day",                      // 日k线
		"1week",                     // 周k线
		"1mon",                      // 月k线
		"1year",                     // 年k线
		"tl",                        // 分时线
		0
	};

	const char* szPercentType[] = {
		"10",                           // 百分之10行情深度
		"20",                           // 百分之20行情深度
		"50",                           // 百分之50行情深度
		"80",                           // 百分之80行情深度
		"100",                          // 百分之100行情深度
		"top",                          // top行情深度
		0
	};


	const int nMarketDepthTopShortLength = 20;		// 短的top行情深度
	const int MAX_PACKAGE_COUNT = 500;              // 请求历史交易明细数据包的最大明细条数
	const int TRADE_PACKAGE_COUNT = 100;            // 实时交易明细数据包的最大明细条数
	const int MAX_TRADE_ID = -1;                    // 最大的交易id，根据这个id获取最新的交易明细
	const int LINE_LIMIT_SIZE = 300;                // 分时线，k线缺省条数
	const int TRADE_DETAIL_LIMIT_SIZE = 300;        // 交易明细缺省条数
	const int AMOUNT_DOT_LENGTH = 4;                // 成交量小数点长度
	const int VOLUME_DOT_LENGTH = 2;                // 成交额小数点长度

	QLatin1String szRestKName[] = {
		QLatin1String("method"),
		QLatin1String("access_key"),
		QLatin1String("created"),
		QLatin1String("sign"),
		QLatin1String("secret_key"),
		QLatin1String("market"),
		QLatin1String("coin_type"),
		QLatin1String("id"),
		QLatin1String("price"),
		QLatin1String("amount"),
		QLatin1String("trade_id"),
		QLatin1String("withdraw_address"),
		QLatin1String("withdraw_amount"),
		QLatin1String("withdraw_coin_id"),
		QLatin1String("account_from"),
		QLatin1String("account_to"),
		QLatin1String("loan_type"),
		QLatin1String("loan_id"),
		QLatin1String("repay_all"),
	};


	const char* szMarketType[] = {
		"cny",
		"usd",
		0
	};

}
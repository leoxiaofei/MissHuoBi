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
		"1min",                      // 1����k��
		"5min",                      // 5����k��
		"15min",                     // 15����k��
		"30min",                     // 30����k��
		"60min",                     // 60����k��
		"1day",                      // ��k��
		"1week",                     // ��k��
		"1mon",                      // ��k��
		"1year",                     // ��k��
		"tl",                        // ��ʱ��
		0
	};

	const char* szPercentType[] = {
		"10",                           // �ٷ�֮10�������
		"20",                           // �ٷ�֮20�������
		"50",                           // �ٷ�֮50�������
		"80",                           // �ٷ�֮80�������
		"100",                          // �ٷ�֮100�������
		"top",                          // top�������
		0
	};


	const int nMarketDepthTopShortLength = 20;		// �̵�top�������
	const int MAX_PACKAGE_COUNT = 500;              // ������ʷ������ϸ���ݰ��������ϸ����
	const int TRADE_PACKAGE_COUNT = 100;            // ʵʱ������ϸ���ݰ��������ϸ����
	const int MAX_TRADE_ID = -1;                    // ���Ľ���id���������id��ȡ���µĽ�����ϸ
	const int LINE_LIMIT_SIZE = 300;                // ��ʱ�ߣ�k��ȱʡ����
	const int TRADE_DETAIL_LIMIT_SIZE = 300;        // ������ϸȱʡ����
	const int AMOUNT_DOT_LENGTH = 4;                // �ɽ���С���㳤��
	const int VOLUME_DOT_LENGTH = 2;                // �ɽ���С���㳤��

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
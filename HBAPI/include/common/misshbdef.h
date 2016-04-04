#ifndef __MISSHBDEF_H__
#define __MISSHBDEF_H__


namespace HBAPI
{
	enum AttributeName {
		AN_SYMBOLID,
		AN_PUSHTYPE,
		AN_SYMBOLLIST,
		AN_MSGTYPE,
		AN_REQUESTINDEX,
		AN_VERSION,
		AN_RETCODE,
		AN_REQUEST,
		AN__ID,
		AN_IDCUR,
		AN_IDPREV,
		AN_TIMEMAX,
		AN_TIMEMIN,
		AN_PAYLOAD,

		AN_TRADEID,
		AN_PRICE,
		AN_TIME,
		AN_AMOUNT,
		AN_DIRECTION,
		AN_TOPBIDS,
		AN_TOPASKS,

		AN_LEVEL,
		AN_ACCUAMOUNT,

		AN_PRICENEW,
		AN_PRICEOPEN,
		AN_PRICEHIGH,
		AN_PRICELOW,
		AN_PRICELAST,
		AN_TOTALAMOUNT,
		AN_AMP,
		AN_TRADES,
		AN_BIDS,
		AN_ASKS,
		AN_COMMISSIONRATIO,
		AN_POOR,
		AN_UPDOWNVOLUME,
		AN_UPDOWNRATIO,
		AN_PRICEAVERAGE,
		AN_VOLUMERATIO,
		AN_TURNVOLUME,
		AN_TURNOVERRATE,
		AN_OUTERDISC,
		AN_INNERDISC,
		AN_TOTALVOLUME,

		AN_PERIOD,
		AN_PERCENT,

		AN_VOLUME,
		AN_COUNT,
		AN_ROW,

		AN_VERSIONOLD,
		AN_BIDINSERT,
		AN_BIDDELETE,
		AN_BIDUPDATE,
		AN_ASKINSERT,
		AN_ASKDELETE,
		AN_ASKUPDATE,

		AN_PRICEASK,
		AN_PRICEBID,
	};

	extern const char* szAttributeName[];

	enum SymbolIdType {
		SIT_BTCCNY, 
		SIT_LTCCNY, 
		SIT_BTCUSD,
	};

	extern const char* szSymbolIdType[];


	// 推送策略常量定义
	enum PushType {
	    PT_PUSHLONG,                          // 长推送
		PT_PUSHSHORT,                         // 短推送
	};

	extern const char* szPushType[];

	// k线周期类型
	enum PeriodType {
		PT_KLINE1MIN,                 // 1分钟k线
		PT_KLINE5MIN,                 // 5分钟k线
		PT_KLINE15MIN,                // 15分钟k线
		PT_KLINE30MIN,                // 30分钟k线
		PT_KLINE60MIN,                // 60分钟k线
		PT_KLINE1DAY,                 // 日k线
		PT_KLINE1WEEK,                // 周k线
		PT_KLINE1MON,                 // 月k线
		PT_KLINE1YEAR,                // 年k线
		PT_KLINETIMELINE,             // 分时线
	};

	extern const char* szPeriodType[];
    
    // 行情深度百分比
	enum PercentType {
		PT_PERCENT10,                 // 百分之10行情深度
		PT_PERCENT20,                 // 百分之20行情深度
		PT_PERCENT50,                 // 百分之50行情深度
		PT_PERCENT80,                 // 百分之80行情深度
		PT_PERCENT100,                // 百分之100行情深度
		PT_PERCENTTOP,                // top行情深度
	};

	extern const char* szPercentType[];

	// 行情协议版本
	enum ProtocolVersion { 
		PV_VERSION_1 = 1, 
		PV_CURRENT = PV_VERSION_1 
	};

    // 错误编码
	enum ErrorCode {
		CODE_OK = 200,                                        // 成功
		CODE_PARAM_ERROR = 601,                               // 参数错误
		CODE_SERVER_ERROR = 701,                              // 服务器错误
	};

	/// 交易方向
	enum DirectionType {
		DT_BUYING = 1, 
		DT_SELLING,
	};

	extern const int MARKET_DEPTH_TOP_SHORT_LENGTH;    // 短的top行情深度
	extern const int MAX_PACKAGE_COUNT;                // 请求历史交易明细数据包的最大明细条数
	extern const int TRADE_PACKAGE_COUNT;              // 实时交易明细数据包的最大明细条数
	extern const int MAX_TRADE_ID;                     // 最大的交易id，根据这个id获取最新的交易明细
	extern const int LINE_LIMIT_SIZE;                  // 分时线，k线缺省条数
	extern const int TRADE_DETAIL_LIMIT_SIZE;          // 交易明细缺省条数
	extern const int AMOUNT_DOT_LENGTH;                // 成交量小数点长度
	extern const int VOLUME_DOT_LENGTH;                // 成交额小数点长度

}



#endif // __MISSHBDEF_H__

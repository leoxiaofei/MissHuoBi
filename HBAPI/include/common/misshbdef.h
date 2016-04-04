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


	// ���Ͳ��Գ�������
	enum PushType {
	    PT_PUSHLONG,                          // ������
		PT_PUSHSHORT,                         // ������
	};

	extern const char* szPushType[];

	// k����������
	enum PeriodType {
		PT_KLINE1MIN,                 // 1����k��
		PT_KLINE5MIN,                 // 5����k��
		PT_KLINE15MIN,                // 15����k��
		PT_KLINE30MIN,                // 30����k��
		PT_KLINE60MIN,                // 60����k��
		PT_KLINE1DAY,                 // ��k��
		PT_KLINE1WEEK,                // ��k��
		PT_KLINE1MON,                 // ��k��
		PT_KLINE1YEAR,                // ��k��
		PT_KLINETIMELINE,             // ��ʱ��
	};

	extern const char* szPeriodType[];
    
    // ������Ȱٷֱ�
	enum PercentType {
		PT_PERCENT10,                 // �ٷ�֮10�������
		PT_PERCENT20,                 // �ٷ�֮20�������
		PT_PERCENT50,                 // �ٷ�֮50�������
		PT_PERCENT80,                 // �ٷ�֮80�������
		PT_PERCENT100,                // �ٷ�֮100�������
		PT_PERCENTTOP,                // top�������
	};

	extern const char* szPercentType[];

	// ����Э��汾
	enum ProtocolVersion { 
		PV_VERSION_1 = 1, 
		PV_CURRENT = PV_VERSION_1 
	};

    // �������
	enum ErrorCode {
		CODE_OK = 200,                                        // �ɹ�
		CODE_PARAM_ERROR = 601,                               // ��������
		CODE_SERVER_ERROR = 701,                              // ����������
	};

	/// ���׷���
	enum DirectionType {
		DT_BUYING = 1, 
		DT_SELLING,
	};

	extern const int MARKET_DEPTH_TOP_SHORT_LENGTH;    // �̵�top�������
	extern const int MAX_PACKAGE_COUNT;                // ������ʷ������ϸ���ݰ��������ϸ����
	extern const int TRADE_PACKAGE_COUNT;              // ʵʱ������ϸ���ݰ��������ϸ����
	extern const int MAX_TRADE_ID;                     // ���Ľ���id���������id��ȡ���µĽ�����ϸ
	extern const int LINE_LIMIT_SIZE;                  // ��ʱ�ߣ�k��ȱʡ����
	extern const int TRADE_DETAIL_LIMIT_SIZE;          // ������ϸȱʡ����
	extern const int AMOUNT_DOT_LENGTH;                // �ɽ���С���㳤��
	extern const int VOLUME_DOT_LENGTH;                // �ɽ���С���㳤��

}



#endif // __MISSHBDEF_H__

#ifndef __ASKSDATA_H__
#define __ASKSDATA_H__


#include <QVector>
#include "hbglobal.h"

class QJsonObject;
class QJsonArray;

namespace HBAPI
{

	///卖单
	class HBAPI_EXPORT AsksData
	{
	public:
		double	dPrice;				///价格
		double	dAmount;			///成交量
		double	dAccuAmount;		///累计委单量
		double	dLevel;				///（猜想）涨跌量：最新价减去开盘价
	};

	void ParseAsksData(const QJsonObject& json, QVector<AsksData>& vecAsksData);

	class HBAPI_EXPORT AskDepthData
	{
	public:
		double	dPrice;				///价格
		double	dAmount;			///成交量
		double	dTotal;				///累计委单量

		bool operator == (const AskDepthData& other) const;
	};

	void ParseAskDepthData(const QJsonObject& json, QList<AskDepthData>& listDepthData);

	class HBAPI_EXPORT AskInsertData
	{
	public:
		double	dPrice;				///价格
		double	dAmount;			///成交量
		int		nRow;				///行数

	};

	void ParseAskInsertData(const QJsonObject& json, QVector<AskInsertData>& vecAskInsertData);

	class HBAPI_EXPORT AskDeleteData
	{
	public:
		int		nRow;				///行数
	};

	void ParsAskDeleteData(const QJsonArray& json, QVector<AskDeleteData>& vecAskDeleteData);

	class HBAPI_EXPORT AskUpdateData
	{
	public:
		double	dPrice;				///价格
		double	dAmount;			///成交量
		int		nRow;				///行数

	};

	void ParseAskUpdateData(const QJsonObject& json, QVector<AskUpdateData>& vecAskUpdateData);



}

#endif // __ASKSDATA_H__

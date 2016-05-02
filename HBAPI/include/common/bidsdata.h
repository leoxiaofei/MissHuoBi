#ifndef __BIDSDATA_H__
#define __BIDSDATA_H__

#include <QVector>
#include "hbglobal.h"

class QJsonObject;
class QJsonArray;

namespace HBAPI
{

	///买单
	class HBAPI_EXPORT BidsData
	{
	public:
		double	dPrice;				///价格
		double	dAmount;			///成交量
		double	dAccuAmount;		///累计委单量
		double	dLevel;
	};


	void ParseBidsData(const QJsonObject& json, QVector<BidsData>& vecBidsData);

	class HBAPI_EXPORT BidDepthData
	{
	public:
		double	dPrice;				///价格
		double	dAmount;			///成交量
		double	dTotal;				///累计委单量

		bool operator == (const BidDepthData& other) const;
	};

	void ParseBidDepthData(const QJsonObject& json, QList<BidDepthData>& listDepthData);

	class HBAPI_EXPORT BidInsertData
	{
	public:
		double	dPrice;				///价格
		double	dAmount;			///成交量
		int		nRow;				///行数

	};

	void ParseBidInsertData(const QJsonObject& json, QVector<BidInsertData>& vecBidInsertData);

	class HBAPI_EXPORT BidDeleteData
	{
	public:
		int		nRow;				///行数

	};

	void ParseBidDeleteData(const QJsonArray& json, QVector<BidDeleteData>& vecBidDeleteData);

	class HBAPI_EXPORT BidUpdateData
	{
	public:
		double	dPrice;				///价格
		double	dAmount;			///成交量
		int		nRow;				///行数

	};

	void ParseBidUpdateData(const QJsonObject& json, QVector<BidUpdateData>& vecBidUpdateData);

}

#endif // __BIDSDATA_H__

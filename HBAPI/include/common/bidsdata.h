#ifndef __BIDSDATA_H__
#define __BIDSDATA_H__

#include <QVector>
#include "hbglobal.h"

class QJsonObject;
class QJsonArray;

namespace HBAPI
{

	///��
	class HBAPI_EXPORT BidsData
	{
	public:
		double	dPrice;				///�۸�
		double	dAmount;			///�ɽ���
		double	dAccuAmount;		///�ۼ�ί����
		double	dLevel;
	};


	void ParseBidsData(const QJsonObject& json, QVector<BidsData>& vecBidsData);

	class HBAPI_EXPORT BidDepthData
	{
	public:
		double	dPrice;				///�۸�
		double	dAmount;			///�ɽ���
		double	dTotal;				///�ۼ�ί����

		bool operator == (const BidDepthData& other) const;
	};

	void ParseBidDepthData(const QJsonObject& json, QList<BidDepthData>& listDepthData);

	class HBAPI_EXPORT BidInsertData
	{
	public:
		double	dPrice;				///�۸�
		double	dAmount;			///�ɽ���
		int		nRow;				///����

	};

	void ParseBidInsertData(const QJsonObject& json, QVector<BidInsertData>& vecBidInsertData);

	class HBAPI_EXPORT BidDeleteData
	{
	public:
		int		nRow;				///����

	};

	void ParseBidDeleteData(const QJsonArray& json, QVector<BidDeleteData>& vecBidDeleteData);

	class HBAPI_EXPORT BidUpdateData
	{
	public:
		double	dPrice;				///�۸�
		double	dAmount;			///�ɽ���
		int		nRow;				///����

	};

	void ParseBidUpdateData(const QJsonObject& json, QVector<BidUpdateData>& vecBidUpdateData);

}

#endif // __BIDSDATA_H__

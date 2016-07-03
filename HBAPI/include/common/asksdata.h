#ifndef __ASKSDATA_H__
#define __ASKSDATA_H__


#include <QVector>
#include "hbglobal.h"

class QJsonObject;
class QJsonArray;

namespace HBAPI
{

	///����
	class HBAPI_EXPORT AsksData
	{
	public:
		double	dPrice;				///�۸�
		double	dAmount;			///�ɽ���
		double	dAccuAmount;		///�ۼ�ί����
		double	dLevel;				///�����룩�ǵ��������¼ۼ�ȥ���̼�
	};

	void ParseAsksData(const QJsonObject& json, QVector<AsksData>& vecAsksData);

	class HBAPI_EXPORT AskDepthData
	{
	public:
		double	dPrice;				///�۸�
		double	dAmount;			///�ɽ���
		double	dTotal;				///�ۼ�ί����

		bool operator == (const AskDepthData& other) const;
	};

	void ParseAskDepthData(const QJsonObject& json, QList<AskDepthData>& listDepthData);

	class HBAPI_EXPORT AskInsertData
	{
	public:
		double	dPrice;				///�۸�
		double	dAmount;			///�ɽ���
		int		nRow;				///����

	};

	void ParseAskInsertData(const QJsonObject& json, QVector<AskInsertData>& vecAskInsertData);

	class HBAPI_EXPORT AskDeleteData
	{
	public:
		int		nRow;				///����
	};

	void ParsAskDeleteData(const QJsonArray& json, QVector<AskDeleteData>& vecAskDeleteData);

	class HBAPI_EXPORT AskUpdateData
	{
	public:
		double	dPrice;				///�۸�
		double	dAmount;			///�ɽ���
		int		nRow;				///����

	};

	void ParseAskUpdateData(const QJsonObject& json, QVector<AskUpdateData>& vecAskUpdateData);



}

#endif // __ASKSDATA_H__

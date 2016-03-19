#ifndef __REQMARKETDEPTHTOP_H__
#define __REQMARKETDEPTHTOP_H__

#include "requestbase.h"

/*
��ʷ���ݽӿ�
��ȡTop�������
*/

namespace HBAPI
{
	class ReqMarketDepthTop : public RequestBase
	{
		REQTYPE(reqMarketDepthTop);
	public:
		ReqMarketDepthTop();
		~ReqMarketDepthTop();

		int SendRequest(SymbolIdType eSymbolId);

	protected:
		virtual bool ReceiveJson(const QJsonObject& json) override;

	};

}

#endif // __REQMARKETDEPTHTOP_H__

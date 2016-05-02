#include "rest\restrequestbase.h"
#include "common\mapkv.h"



namespace HBAPI
{

	void RestRequestBase::SetSendFunc(const SendRestFunc& funcSend)
	{
		m_funcSend = funcSend;
	}

	void RestRequestBase::SendRest(MapKV& mapParams, MapKV& mapExtra /*= MapKV()*/)
	{
		m_funcSend(mapParams, mapExtra, this);
	}

	void RestRequestBase::SendRest(MapKV& mapParams)
	{
		m_funcSend(mapParams, MapKV(), this);
	}

}

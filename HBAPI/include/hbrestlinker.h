#ifndef __HBRESTLINKER_H__
#define __HBRESTLINKER_H__

#include "hbglobal.h"

#include <QObject>
#include <functional>


class QNetworkReply;

namespace HBAPI
{
	typedef std::function<void(long, const QByteArray&)> FuncRecvRest;

class HBAPI_EXPORT HbRestLinker : public QObject
{
public:
	HbRestLinker(QObject* parent = 0);
	~HbRestLinker();

	void SetRecvFunc(const FuncRecvRest& funcRecvRest);

	void SetUrl(const QUrl& url);

	long PostData(const QByteArray& ba);

public slots:
	void slot_ReceiveData(QNetworkReply *reply);

protected:
	void Init();

private:
	class Impl;
	QScopedPointer<Impl> m_pImpl;
};

}



#endif // __HBRESTLINKER_H__

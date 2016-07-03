#ifndef __HBMARKETLINKER_H__
#define __HBMARKETLINKER_H__

#include "hbglobal.h"
#include <QObject>
#include <functional>

namespace HBAPI
{
	typedef std::function<void(const QString &, const QVariantMap &)> FuncEmitMarket;
	typedef std::function<void(const QJsonArray&)> FuncRecvMarket;

	class HBAPI_EXPORT HbMarketLinker : public QObject
	{
		Q_OBJECT
	public:
		HbMarketLinker(QObject* parent = 0);
		~HbMarketLinker();

		void SetUrl(const QUrl& url);
		void SetRecvFunc(const FuncRecvMarket& fpRequest, const FuncRecvMarket& fpMessage);

		void Connect();
		void Disconnect();

		bool IsConnected() const;
		FuncEmitMarket GetSendFunc() const;

	signals:
		void signal_Connected();
		void signal_Disconnected();
		void signal_Asystole();

	public slots:
		void on_sioClient_heartbeatReceived();
		void on_sioClient_messageReceived(const QString& message);
		void on_sioClient_errorReceived(const QString& reason, const QString& advice);
		void on_sioClient_connected(const QString& endpoint);
		void on_sioClient_disconnected(const QString& endpoint);

	private:
		class Impl;
		QScopedPointer<Impl> m_pImpl;
	};

}


#endif // __HBMARKETLINKER_H__

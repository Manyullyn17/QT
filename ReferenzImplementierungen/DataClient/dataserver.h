#pragma once

#include "sinedataproducer.h"

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <memory>
#include <set>

class DataServer : public QObject
{
    Q_OBJECT
public:
    DataServer(SineDataProducer& sine_producer);
    bool startServer(QString ip, int port);
    void stopServer();

public slots:
    void newConnection();
    void readyRead();
    void clientDisconnected();

private:
    void sendErrorMessage(QTcpSocket& socket) const;

private:
    std::unique_ptr<QTcpServer> m_tcp_server;
    std::set<std::shared_ptr<QTcpSocket>> m_connections;

    bool m_server_closing = false;

    QTime m_start_time{QTime::currentTime()};
    QTime m_segment_start_time{m_start_time};
    SineDataProducer& m_sine_producer;
};


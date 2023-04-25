#include "dataserver.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>

DataServer::DataServer(SineDataProducer& sine_producer)
    : m_tcp_server{new QTcpServer{this}}
    , m_sine_producer{sine_producer}
{

}

bool DataServer::startServer(QString ip, int port)
{
    connect(m_tcp_server.get(), SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(m_tcp_server->listen(QHostAddress(ip), port))
    {
        return true;
    }
    return false;
}

void DataServer::stopServer()
{
    if(m_tcp_server->isListening())
    {
        m_server_closing = true;
        foreach (const auto socket, m_connections)
        {
            socket->close();
        }
        m_connections.clear();
        m_tcp_server->close();
        m_server_closing = false;
    }
}

void DataServer::newConnection()
{
    auto newClientConnetion = m_tcp_server->nextPendingConnection();
    m_connections.insert(std::make_shared<QTcpSocket>(newClientConnetion));

    connect(newClientConnetion, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(newClientConnetion, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

}

void DataServer::readyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    QString msg = socket->readAll();
    if(msg.contains("READ_DATA"))
    {
        auto request = msg.split(" ");
        if (request.size() != 3)
        {
            sendErrorMessage(*socket);
            return;
        }

        bool ok;
        int start_time = request[1].toInt(&ok);
        if(!ok)
        {
            sendErrorMessage(*socket);
            return;
        }

        int end_time = request[2].toInt(&ok);
        if(!ok)
        {
            sendErrorMessage(*socket);
            return;
        }


        const auto& data = m_sine_producer.getData(QTime::fromMSecsSinceStartOfDay(start_time),
                                                   QTime::fromMSecsSinceStartOfDay(end_time));
        QByteArray response;
        response.append(QByteArray::number(data.size()));

        for(const auto& dp : data)
        {
            response.append(" ");
            response.append(QByteArray::number(dp.first.msecsSinceStartOfDay()));
            response.append(" ");
            response.append(QByteArray::number(dp.second));
        }
        socket->write(response);


    }
    else
    {
        sendErrorMessage(*socket);
    }

}

void DataServer::clientDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

    if(!m_server_closing)
    {
        m_connections.erase(m_connections.find(std::make_shared<QTcpSocket>(socket)));
    }
}

void DataServer::sendErrorMessage(QTcpSocket& socket) const
{
    QString error_msg{"Invalid Message!"};
    socket.write(error_msg.toLocal8Bit().data());
}

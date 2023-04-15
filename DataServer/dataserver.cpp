#include "dataserver.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>

DataServer::DataServer(const DataProducer& sine_producer)
    : m_tcp_server{new QTcpServer{this}}
    , m_data_producer{sine_producer}
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
        for (const auto& socket: m_connections)
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
    m_connections.insert(newClientConnetion);

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
        if (request.size() != 2)
        {
            sendErrorMessage(*socket);
            return;
        }

        bool ok;
        int duration = request[1].toInt(&ok);
        if(!ok)
        {
            sendErrorMessage(*socket);
            return;
        }

        const auto& data = m_data_producer.getData(duration);
        QByteArray response;
        //response.append(QByteArray::number(data.size()));
        int idx = 0;
        const int num_values = data.size();
        for(const auto& dp : data)
        {
            response.append(QByteArray::number(dp.first.msecsSinceStartOfDay()));
            response.append(" ");
            response.append(QByteArray::number(dp.second));
            if (++idx < num_values)
                response.append(" ");
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
        m_connections.erase(m_connections.find(socket));
    }
}

void DataServer::sendErrorMessage(QTcpSocket& socket) const
{
    QString error_msg{"Invalid Message!"};
    socket.write(error_msg.toLocal8Bit().data());
}

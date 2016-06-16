#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QMessageBox>
#include <QtWidgets>
#include "stdlib.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    hotelServer(Q_NULLPTR),
    networkSession(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));

        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
                QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }
        networkSession = new QNetworkSession(config, this);
        connect(networkSession, &QNetworkSession::opened, this, &MainWindow::sessionOpened);
        networkSession->open();
        hotelInfo =tr("Title: Hampton Inn\n"
                  "Number of available rooms: 50\n"
                  "Number of floors: 10\n"
                  "Number of unavailable rooms: 5\n");
    }
    else {//if none of this can be done then it opens session straight away
            sessionOpened();}
    connect(ui->quitButton, &QAbstractButton::clicked, this, &QWidget::close);
//!This might need to change so that I can send data that is not just hotelInfo
    connect(hotelServer, &QTcpServer::newConnection, this, &MainWindow::sendHotelInfo);
    //!
    setWindowTitle("Hotel Server");
}

void MainWindow::sessionOpened()
{
    if(networkSession){
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else{
            id=config.identifier();        }
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }
    hotelServer = new QTcpServer(this);
    if(!hotelServer->listen())
    {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(hotelServer->errorString()));
        close();
        return;
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;

        }
    }
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    ui->statusLabel->setText("Server is now running. Please open client application.");
    ui->IPLabel->setText(tr("ServerIP: %1").arg(ipAddress));
    ui->portLabel->setText(tr("Port: %1").arg(hotelServer->serverPort()));
}

void MainWindow::sendHotelInfo()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << hotelInfo;
    out.device()->seek(0);//This goes back to beginning to overwrite quint value
    out << (quint16)(block.size() - sizeof(quint16));//for actual data size
    //TCPSocket work
    QTcpSocket *clientConnection = hotelServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);
    clientConnection->write(block);
    clientConnection->disconnectFromHost();

}

void MainWindow::sendRoomData()
{
    connect(this,SIGNAL(socketConnected()),curRoomData,SLOT(getRoom()));
    emit socketConnected();
    roomData *curRoomData = new roomData();
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;//REMEMBER TO DECLARE CLASS INHERITS QOBJECT
    out<<curRoomData->roomInfo;//this is the roomData
    out.device()->seek(0);
    out<< (quint16)(block.size()-sizeof(quint16));
    QTcpSocket *clientConnection = hotelServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);
    clientConnection->write(block);
    clientConnection->disconnectFromHost();
}
void MainWindow::sendGuestData()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;//this is guestData
    out<<curGuestData->guestInfo;
    out.device()->seek(0);
    out<<(quint16)(block.size()-sizeof(quint16));
    QTcpSocket *clientConnection = hotelServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);
    clientConnection->write(block);
    clientConnection->disconnectFromHost();
}

MainWindow::~MainWindow()
{
    delete ui;
}

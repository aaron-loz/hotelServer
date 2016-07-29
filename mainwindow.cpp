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
    //sets manager incase something changes
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

    }

    else {//opens session straight away
            sessionOpened();}

    hotelInfo =tr("Hotel Name: Hampton Inn\n"
                      "Number of available rooms: 50\n"
                      "Number of floors: 10\n"
                      "Number of unavailable rooms: 5");

    //hotelInfo set for mock purposes
    connect(ui->quitButton, &QAbstractButton::clicked, this, &QWidget::close);
    connect(hotelServer, &QTcpServer::newConnection, this, &MainWindow::sendHotelInfo);

    setWindowTitle("Hotel Server");
}

void MainWindow::sessionOpened()
{
    //saves any settings needed
    if(networkSession){
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else{
            id=config.identifier();}
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    //in case problem starting server.
    hotelServer = new QTcpServer(this);
    if(!hotelServer->listen())
    {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(hotelServer->errorString()));
        close();
        return;
    }

    //for user readability, ipaddress is labeled
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (ipAddress.isEmpty()){
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();}

    ui->statusLabel->setText("Server is now running. Please open client application.");
    ui->IPLabel->setText(tr("ServerIP: %1").arg(ipAddress));
    ui->portLabel->setText(tr("Port: %1").arg(hotelServer->serverPort()));

}

void MainWindow::sendHotelInfo()
{
    //double pointer to allow for array to work correctly.
    roomData **curRoomData = new roomData*[50];
    for(int i=0;i<50;i++){
        curRoomData[i]= new roomData();
    }

    guestData **curGuestData = new guestData*[3];
    for(int i=0;i<3;i++){
        curGuestData[i]= new guestData();
    }
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    out << hotelInfo;
    //sets data for streaming and saving file for client so client does not need to connect to server.
    for(int i=0;i<=49;i++){
    curRoomData[i]->setRoomData(i);
    out <<(qint32)curRoomData[i]->num;
    out<<(QString)curRoomData[i]->bedType;
    out<<(bool)curRoomData[i]->occupied;
    }
    for(int i=0;i<3;i++){
        curGuestData[i]->setGuestData(i, 100+i);
        out<<(QString)curGuestData[i]->fullName;
        out<<(qint32)curGuestData[i]->checkInDate;
        out<<(qint32)curGuestData[i]->numNights;
        out<<(qint32)curGuestData[i]->roomNumAssigned;
    }

    out.device()->seek(0);//This goes back to beginning to overwrite quint value
    out << (quint16)(block.size() - sizeof(quint16));//for actual data size

    clientConnection = hotelServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected,
            clientConnection, &QObject::deleteLater);
    clientConnection->write(block);
    clientConnection->disconnectFromHost();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_quitButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you wanna Quit?",
                                  QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        QCoreApplication::exit();}
}

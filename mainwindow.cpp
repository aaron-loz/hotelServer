#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    hotelServer(Q_NULLPTR),
    networkSession(0),
    ui(new Ui::MainWindow)
{
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
        connect(networkSession, &QNetworkSession::opened, this, &server::sessionOpened);
        statusLabel->setText(tr("Opening network session."));
        networkSession->open();
    }
    else {//if none of this can be done then it opens session straight away
            sessionOpened();}

    ui->setupUi(this);
}

void MainWindow::sessionOpened()
{

}

void MainWindow::sendHotelData()
{

}

void MainWindow::sendRoomData()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "guestdata.h"
#include "roomdata.h"

#include <QString>
#include <QDialog>
#include <QMainWindow>
#include <QtNetwork>

QT_USE_NAMESPACE
class QTcpServer;
class QNetworkSession;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void sessionOpened();
    void sendGuestData();
    void sendHotelInfo();
    void on_quitButton_clicked();

private:
    QNetworkSession *networkSession;
    QTcpServer *hotelServer;
    guestData *curGuestData;
    roomData *curRoomData;
    QString hotelInfo;
    Ui::MainWindow *ui;
    QTcpSocket *clientConnection;
signals:
    void socketConnected();
};
#endif // MAINWINDOW_H

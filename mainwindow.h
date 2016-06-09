#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "guestdata.h"
#include "roomdata.h"

#include <QDialog>
#include <QMainWindow>

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
    void sendHotelData();
    void sendRoomData();
private:
    QNetworkSession *networkSession;
    QTcpServer *hotelServer;
    guestData *curGuestData;
    roomData *curRoomData;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

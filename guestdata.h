#ifndef GUESTDATA_H
#define GUESTDATA_H
#include <QString>
#include <QWidget>

class guestData: public QObject
{
    Q_OBJECT
public:
    guestData();
public slots:
    void setGuestData(int &i, int roomNum);
    void setCheckIn();
    void getGuestData();
public:
QString fullName;
int numNights;
int checkInDate;
int roomNumAssigned;
};

#endif // GUESTDATA_H

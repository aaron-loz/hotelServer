#ifndef GUESTDATA_H
#define GUESTDATA_H
#include <QString>
#include <QWidget>

class guestData: public QObject
{
    Q_OBJECT
public:
    guestData();
    QString guestInfo;
private slots:
    void setGuestData();
    void setCheckIn();
    void getGuestData();
private:
QString fullName;
int numNights;
int checkInDate;
int roomNumAssigned;
};

#endif // GUESTDATA_H

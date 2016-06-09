#ifndef GUESTDATA_H
#define GUESTDATA_H


class guestData
{
public:
    guestData();
private slots:
    void setGuestData();
    void setCheckIn();
    void getGuestData();
private:
string fullName;
int numNights;
int checkInDate;
int roomNumAssigned;
};

#endif // GUESTDATA_H

#include "guestdata.h"

guestData::guestData()
{

}

void guestData::setCheckIn(){

}

void guestData::setGuestData(int &i, int roomNum){
    switch(i){
    case 0:
        fullName="Aaron L.";
        numNights = 3;
        checkInDate = 70916;
        roomNumAssigned = roomNum;
        break;
    case 1:
        fullName="Andrew L.";
        numNights = 5;
        checkInDate = 70216;
        roomNumAssigned = roomNum;
        break;
    case 2:
        fullName="Isabella L.";
        numNights = 1;
        checkInDate = 71316;
        roomNumAssigned = roomNum;
        break;
    }

}

void guestData::getGuestData(){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
}

#include "guestdata.h"

guestData::guestData()
{

}

void guestData::setCheckIn(){

}

void guestData::setGuestData(){

}

void guestData::getGuestData(){
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
}

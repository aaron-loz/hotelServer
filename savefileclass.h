#ifndef SAVEFILECLASS_H
#define SAVEFILECLASS_H
#include "roomdata.h"
#include "guestdata.h"

class saveFileClass : public QFile
{
public:
    saveFileClass();
    QString hotelInfo;
    roomData hotelRoomInfo[49];
    guestData guestsInfo[5];
    QFile initializedFile;
};

#endif // SAVEFILECLASS_H

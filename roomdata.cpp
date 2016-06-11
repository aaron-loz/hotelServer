#include "roomdata.h"

roomData::roomData()
{
    roomData allRooms[50];
    for(int i=0;i<50;i++)
    {
        //Set at random for each rooms assignment
    }
}

void roomData::setBedData(){

}

void roomData::setRoomData(){


}

void roomData::getRoom(){
    QString isRoomSmoking;
    if(smoking)
        isRoomSmoking = "Yes";
    else
        isRoomSmoking = "No";
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out<<"Room Number: "<<num<<"Number of beds"<<numBeds
      <<"smoking: "<<isRoomSmoking<<"Floor: "<<floorLvl
     <<"bed Type: "<<bedType;
}

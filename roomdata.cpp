#include "roomdata.h"
#include <QtDebug>
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
    //In The Future: When Client asks to set room stuff, this will do change to the roomData
    roomData rooms[49];
    for(int i=0;i<49;i+=2)
    {
        rooms[i].smoking =false;
        rooms[i].bedType ="King";
        for(int n=0;n<49;n++)
        {

          if( n<10){
               rooms[n].floorLvl=1;
               qDebug()<<"1";
          }
          else if( n>=10 &&n<20)
               rooms[n].floorLvl=2;
          else if(n>=20 &&n<30)
               rooms[n].floorLvl=3;
          else if( n>=30 && n<40)
               rooms[n].floorLvl=4;
          else{
               rooms[n].floorLvl=5;
               qDebug()<<"2";}
        }
    }
    for(int i=1; i<49;i+=2)
    {
        rooms[i].smoking = true;
        rooms[i].bedType = "Full";
    }
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
    roomInfo="Room Number: ",num,"\nNumber of beds: ",numBeds
           ,"\nsmoking: ",isRoomSmoking,"\nFloor: ",floorLvl
           ,"\nbed Type: ",bedType;
}

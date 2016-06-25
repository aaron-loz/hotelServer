#include "roomdata.h"
#include <QtDebug>
roomData::roomData()
{
}


void roomData::setRoomData(roomData &rooms , int &i){
    //In The Future: When Client asks to set room stuff, this will do change to the roomData
    if(i%2==0){
        rooms.smoking =false;
        rooms.bedType ="King";
        if(i%3==0)
            rooms.numBeds=2;
        else
            rooms.numBeds=1;
    }
    else{
        rooms.smoking = true;
        rooms.bedType = "Full";
        if(i%3==0)
            rooms.numBeds=2;
        else
            rooms.numBeds=1;
    }

      if( i<5)
      {
           rooms.floorLvl=1;
             rooms.num=100+i;
      }
      else if( i>=5 &&i<10)
      {
           rooms.floorLvl=2;
           rooms.num=200+i;
      }
      else if(i>=10 && i<15)
      {
           rooms.floorLvl=3;
            rooms.num=300+i;
      }
      else if(i>=15 &&i<20)
      {
           rooms.floorLvl=4;
            rooms.num=400+i;
      }
      else if( i>=20 && i<25)
      {
           rooms.floorLvl=5;
            rooms.num=500+i;
      }
      else if(i>=25 && i<30)
      {
           rooms.floorLvl=6;
            rooms.num=600+i;
      }
      else if(i>=30 && i<35)
      {
          rooms.floorLvl =7;
           rooms.num=700+i;
      }
      else if(i>=35 && i<40)
      {
          rooms.floorLvl =8;
           rooms.num=800+i;
      }
      else if(i>=40 && i<45)
      {
          rooms.floorLvl =9;
          for(int i=0;i<5;i++){
           rooms.num=900+i;}
      }
      else
      {
          rooms.floorLvl =10;
          for(int i=0;i<5;i++){
           rooms.num=1000+i;}
      }

    if(i<3){
        //For now the first three rooms will be occupied, I want to make this random
        rooms.occupied = true;
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

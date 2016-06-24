#include "roomdata.h"
#include <QtDebug>
roomData::roomData()
{
    setRoomData();
}


void roomData::setRoomData(){
    //In The Future: When Client asks to set room stuff, this will do change to the roomData
    roomData rooms[49];
    for(int i=0;i<49;i+=2)
    {
        rooms[i].smoking =false;
        rooms[i].bedType ="King";
        if(i%3==0)
            rooms[i].numBeds=2;
        else
            rooms[i].numBeds=1;
    }
    for(int i=1; i<49;i+=2)
    {
        rooms[i].smoking = true;
        rooms[i].bedType = "Full";
        if(i%3==0)
            rooms[i].numBeds=2;
        else
            rooms[i].numBeds=1;
    }
    for(int n=0;n<49;n++)
    {
      if( n<5)
      {
           rooms[n].floorLvl=1;
            for(int i=0;i<5;i++){
             rooms[n].num=100+i;}
      }
      else if( n>=5 &&n<10)
      {
           rooms[n].floorLvl=2;
           for(int i=0;i<5;i++){
            rooms[n].num=200+i;}
      }
      else if(n>=10 && n<15)
      {
           rooms[n].floorLvl=3;
           for(int i=0;i<5;i++){
            rooms[n].num=300+i;}
      }
      else if(n>=15 &&n<20)
      {
           rooms[n].floorLvl=4;
           for(int i=0;i<5;i++){
            rooms[n].num=400+i;}
      }
      else if( n>=20 && n<25)
      {
           rooms[n].floorLvl=5;
           for(int i=0;i<5;i++){
            rooms[n].num=500+i;}
      }
      else if(n>=25 && n<30)
      {
           rooms[n].floorLvl=6;
           for(int i=0;i<5;i++){
            rooms[n].num=600+i;}
      }
      else if(n>=30 && n<35)
      {
          rooms[n].floorLvl =7;
          for(int i=0;i<5;i++){
           rooms[n].num=700+i;}
      }
      else if(n>=35 && n<40)
      {
          rooms[n].floorLvl =8;
          for(int i=0;i<5;i++){
           rooms[n].num=800+i;}
      }
      else if(n>=40 && n<45)
      {
          rooms[n].floorLvl =9;
          for(int i=0;i<5;i++){
           rooms[n].num=900+i;}
      }
      else
      {
          rooms[n].floorLvl =10;
          for(int i=0;i<5;i++){
           rooms[n].num=1000+i;}
      }
    }
    for(int i=0;i<3;i++){
        //For now the first three rooms will be occupied, I want to make this random
        rooms[i].occupied = true;
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

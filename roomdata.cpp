#include "roomdata.h"
#include <QtDebug>
roomData::roomData()
{
}

//sets room info, but static
void roomData::setRoomData(int &i){
    occupied =false;
    if(i%2==0){
        smoking =false;
        bedType ="King";
        if(i%3==0)
            numBeds=2;
        else
            numBeds=1;
    }
    else{
        smoking = true;
        bedType = "Full";
        if(i%3==0)
            numBeds=2;
        else
            numBeds=1;
    }
      if( i<5)
      {
           floorLvl=1;
             num=100+(i%5);
      }
      else if( i>=5 &&i<10)
      {
           floorLvl=2;
           num=200+(i%5);
      }
      else if(i>=10 && i<15)
      {
           floorLvl=3;
            num=300+(i%5);
      }
      else if(i>=15 &&i<20)
      {
           floorLvl=4;
            num=400+(i%5);
      }
      else if( i>=20 && i<25)
      {
           floorLvl=5;
            num=500+(i%5);
      }
      else if(i>=25 && i<30)
      {
           floorLvl=6;
            num=600+(i%5);
      }
      else if(i>=30 && i<35)
      {
          floorLvl =7;
           num=700+(i%5);
      }
      else if(i>=35 && i<40)
      {
          floorLvl =8;
           num=800+(i%5);
      }
      else if(i>=40 && i<45)
      {
          floorLvl =9;
           num=900+(i%5);
      }
      else
      {
          floorLvl =10;
           num=1000+(i%5);
      }

    if(i<3){
        //For now the first three rooms will be set, I want to make this random
        occupied = true;
    }
}

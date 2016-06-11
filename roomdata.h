#ifndef ROOMDATA_H
#define ROOMDATA_H
#include<QWidget>

class roomData: public QObject
{
    Q_OBJECT
public:
    roomData();
public slots:
void setBedData();
void setRoomData();
void getRoom();
private:
int num;
int numBeds;
bool smoking;
int floorLvl;
int bedType;
};

#endif // ROOMDATA_H
#ifndef ROOMDATA_H
#define ROOMDATA_H
#include<QWidget>

class roomData: public QObject
{
    Q_OBJECT
public:
    roomData();
    QString roomInfo;
public slots:
void setRoomData(int &i);

public:
int num;
int numBeds;
bool smoking;
bool occupied;
int floorLvl;
QString bedType;
};

#endif // ROOMDATA_H

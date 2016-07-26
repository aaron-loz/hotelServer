#include "savefileclass.h"

saveFileClass::saveFileClass()
{//to keep mainwindow from being bloated, saveFile is seperate
    hotelInfo =tr("Hotel Name: Hampton Inn\n"
                      "Number of available rooms: 50\n"
                      "Number of floors: 10\n"
                      "Number of unavailable rooms: 5");"
}

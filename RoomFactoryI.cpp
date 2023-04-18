#include "RoomFactoryI.h"
#include "RoomI.h"

Room *RoomFactoryI::createRoom(string name)
{
    cout << "createRoom()" << endl;
    return new RoomI();
}

double RoomFactoryI::getServerLoad()
{
    cout << "getServerLoad()" << endl;
}
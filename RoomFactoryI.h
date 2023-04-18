#include <Chat.h>
#include <Ice/Ice.h>

#ifndef __ROOM_FACTORY_I_H__
#define __ROOM_FACTORY_I_H__

using namespace std;
using namespace Chat;

class RoomFactoryI : public RoomFactory
{
public:
    virtual Room *createRoom(string name);
    virtual double getServerLoad();
};

#endif  // __ROOM_FACTORY_I_H__
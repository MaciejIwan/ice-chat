#ifndef ROOM_FACTORY_I_H
#define ROOM_FACTORY_I_H

#include <Ice/Ice.h>

#include "Chat.h"

using namespace std;
using namespace Chat;

class RoomFactoryI : public RoomFactory {
   public:
    RoomFactoryI(const LobbyPrx& lobby);

    virtual RoomPrx createRoom(const string& name, const Ice::Current& current);
    virtual double getServerLoad(const Ice::Current& current);

   private:
    LobbyPrx lobby;
};

#endif

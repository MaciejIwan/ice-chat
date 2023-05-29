#ifndef LOBBY_I_H
#define LOBBY_I_H

#include <Ice/Ice.h>
#include "Chat.h"

using namespace std;
using namespace Chat;

class LobbyI : public Lobby
{
public:
    virtual void registerUser(const UserPrx& user, const std::string& password, const Ice::Current& current);
    virtual void loginUser(const UserPrx& user, const std::string& password, const Ice::Current& current);
    virtual void logout(const Ice::Current& current);
    virtual Rooms getRooms(const Ice::Current& current);
    virtual RoomPrx createRoom(const std::string& name, const Ice::Current& current);
    virtual RoomPrx findRoom(const std::string& name, const Ice::Current& current);
    virtual Users listUsers(const Ice::Current& current);
    virtual void registerRoomFactory(const RoomFactoryPrx& factory, const Ice::Current& current);
    virtual void unregisterRoomFactory(const RoomFactoryPrx& factory, const Ice::Current& current);
};

#endif

#ifndef LOBBY_I_H
#define LOBBY_I_H

#include <Ice/Ice.h>
#include "Chat.h"
#include "RoomFactoryI.h"

using namespace std;
using namespace Chat;

class LobbyI : public Lobby
{
public:
    virtual void _cpp_register(const UserPrx& user, const std::string& password, const Ice::Current& current);
    virtual void login(const UserPrx& user, const std::string& password, const Ice::Current& current);
    virtual void logout(const UserPrx& user, const Ice::Current& current);
    virtual Rooms getRooms(const Ice::Current& current);
    virtual RoomPrx createRoom(const std::string& name, const Ice::Current& current);
    virtual RoomPrx findRoom(const std::string& name, const Ice::Current& current);
    virtual Users ListUsers(const Ice::Current& current);
    virtual void RegisterRoomFactory(const RoomFactoryPrx& factory, const Ice::Current& current);
    virtual void UnregisterRoomFactory(const RoomFactoryPrx& factory, const Ice::Current& current);
private:
    Rooms rooms;
    Users registeredUsers;
    Users loggedUsers;
    // RoomFactoryI roomFactory = RoomFactoryI();
};

#endif

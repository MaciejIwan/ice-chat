#include <Chat.h>
#include <Ice/Ice.h>

#ifndef __LOBBY_I_H__
#define __LOBBY_I_H__

using namespace std;
using namespace Chat;

class LobbyI : public Lobby {
   public:
    LobbyI();
    virtual void login(User *user, string password, const Ice::Current &);
    virtual void _cpp_register(User *user, string password, const Ice::Current &);
    virtual void logout(const Ice::Current &);
    virtual Rooms getRooms(const Ice::Current &);
    virtual Room *createRoom(string name, const Ice::Current &);
    virtual Room *findRoom(string name, const Ice::Current &);
    virtual Users ListUsers(const Ice::Current &);

    virtual void RegisterRoomFactory(RoomFactory *factory, const Ice::Current &);
    virtual void UnregisterRoomFactory(RoomFactory *factory, const Ice::Current &);
};

#endif  // __LOBBY_I_H__
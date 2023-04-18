#include <Chat.h>
#include <Ice/Ice.h>

#ifndef __ROOM_I_H__
#define __ROOM_I_H__

using namespace std;
using namespace Chat;

class RoomI : public Room {
   public:
    RoomI();
    virtual void join(User *user, const Ice::Current &);
    virtual void sendMessage(User *user, string message, const Ice::Current &);
    virtual void leave(User *user, const Ice::Current &);
    virtual Users ListUsers(const Ice::Current &);
};

#endif  // __ROOM_I_H__
#include <Chat.h>
#include <Ice/Ice.h>

#ifndef __USER_I_H__
#define __USER_I_H__

using namespace std;
using namespace Chat;

class UserI : public User {
   public:
    virtual void sendMessage(Room *room, User *user, string message, const Ice::Current &);
    virtual void sendPrivateMessage(User *user, string message, const Ice::Current &);
    virtual string getName(const Ice::Current &);
    virtual UserStatus getStatus(const Ice::Current &);
};

#endif  // __USER_I_H__
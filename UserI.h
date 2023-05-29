#ifndef USER_I_H
#define USER_I_H

#include <Ice/Ice.h>

#include "Chat.h"

using namespace std;
using namespace Chat;

class UserI : public User {
   public:
    UserI(const string& name);

    virtual void sendMessage(const RoomPrx& room, const UserPrx& user, const string& message, const Ice::Current& current);
    virtual void sendPrivateMessage(const UserPrx& user, const string& message, const Ice::Current& current);
    virtual void receiveMessage(const string& message, const Ice::Current& current);
    virtual string getName(const Ice::Current& current);
    virtual UserStatus getStatus(const Ice::Current& current);

   private:
    string name;
    UserStatus status;
};

#endif

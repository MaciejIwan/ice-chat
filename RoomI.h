#ifndef ROOM_I_H
#define ROOM_I_H

#include <Ice/Ice.h>
#include "Chat.h"

using namespace std;
using namespace Chat;

class RoomI : public Room
{
public:
    RoomI(const std::string& name, const UserPrx& owner);
    RoomI(const std::string& name);

    virtual void join(const UserPrx& user, const Ice::Current& current);
    virtual void sendMessage(const UserPrx& user, const std::string& message, const Ice::Current& current);
    virtual void leave(const UserPrx& user, const Ice::Current& current);
    virtual Users ListUsers(const Ice::Current& current);
    virtual std::string getName(const Ice::Current& current);

private:
    bool findUser(const UserPrx& user);
    std::vector<UserPrx>::iterator findUserIterator(const UserPrx& user);

    std::string name;
    // UserPrx owner;
    std::vector<UserPrx> users;
};

#endif

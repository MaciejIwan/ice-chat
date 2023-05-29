#include "RoomI.h"

RoomI::RoomI(const std::string& name, const UserPrx& owner) : name(name), owner(owner) {}

void RoomI::join(const UserPrx& user, const Ice::Current& current)
{
    if (findUser(user))
    {
        throw UserExists();
    }
    users.push_back(user);
}

void RoomI::sendMessage(const UserPrx& user, const std::string& message, const Ice::Current& current)
{
    if (!findUser(user))
    {
        throw AccessDenied();
    }
    for (const auto& u : users)
    {
        u->sendPrivateMessage(user, message);
    }
}

void RoomI::leave(const UserPrx& user, const Ice::Current& current)
{
    auto it = findUserIterator(user);
    if (it != users.end())
    {
        users.erase(it);
    }
}

Users RoomI::listUsers(const Ice::Current& current)
{
    auto userList = Users();
    for (const auto& user : users)
    {
        userList.push_back(user);
    }
    return userList;
}

bool RoomI::findUser(const UserPrx& user)
{
    return findUserIterator(user) != users.end();
}

std::vector<UserPrx>::iterator RoomI::findUserIterator(const UserPrx& user)
{
    return std::find(users.begin(), users.end(), user);
}

#include <Ice/Ice.h>
#include "Chat.h"
#include <memory>

using namespace std;
using namespace Chat;

class RoomI : public Room
{
public:
    RoomI(const std::string& name, const UserPrx& owner) : name(name), owner(owner) {}

    virtual void join(const UserPrx& user, const Ice::Current& current)
    {
        if (findUser(user))
        {
            throw UserExists();
        }
        users.push_back(user);
    }

    virtual void sendMessage(const UserPrx& user, const std::string& message, const Ice::Current& current)
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

    virtual void leave(const UserPrx& user, const Ice::Current& current)
    {
        auto it = findUserIterator(user);
        if (it != users.end())
        {
            users.erase(it);
        }
    }

    virtual Users listUsers(const Ice::Current& current)
    {
        auto userList = Users();
        for (const auto& user : users)
        {
            userList.push_back(user);
        }
        return userList;
    }

private:
    bool findUser(const UserPrx& user)
    {
        return findUserIterator(user) != users.end();
    }

    std::vector<UserPrx>::iterator findUserIterator(const UserPrx& user)
    {
        return std::find(users.begin(), users.end(), user);
    }

    std::string name;
    UserPrx owner;
    std::vector<UserPrx> users;
};

class RoomFactoryI : public RoomFactory
{
public:
    RoomFactoryI(const LobbyPrx& lobby) : lobby(lobby) {}

    virtual RoomPrx createRoom(const string& name, const Ice::Current& current)
    {
        try
        {
            return lobby->findRoom(name);
        }
        catch (const RoomExists&)
        {
            throw RoomExists();
        }
        catch (const AccessDenied&)
        {
            throw AccessDenied();
        }
    }

    virtual double getServerLoad(const Ice::Current& current)
    {
        // Provide an appropriate implementation for the server load calculation
        // For simplicity, return a constant value.
        return 0.5;
    }

private:
    LobbyPrx lobby;
};

class UserI : public User
{
public:
    UserI(const string& name) : name(name), status(UserStatus::Offline) {}

    virtual void sendMessage(const RoomPrx& room, const UserPrx& user, const string& message, const Ice::Current& current)
    {
        room->sendMessage(user, message);
    }

    virtual void sendPrivateMessage(const UserPrx& user, const string& message, const Ice::Current& current)
    {
        // user->receivePrivateMessage(message, this->ice_this());
    }

    virtual string getName(const Ice::Current& current)
    {
        return name;
    }

    virtual UserStatus getStatus(const Ice::Current& current)
    {
        return status;
    }

private:
    string name;
    UserStatus status;
};

class LobbyI : public Lobby
{
public:
    virtual void _cpp_register(const UserPrx& user, const string& password, const Ice::Current& current)
    {
        // Handle user registration logic here
        // ...
    }

    virtual void login(const UserPrx& user, const string& password, const Ice::Current& current)
    {
        // Handle user login logic here
        // ...
    }

    virtual void logout(const Ice::Current& current)
    {
        // Handle user logout logic here
        // ...
    }

    virtual Rooms getRooms(const Ice::Current& current)
    {
        auto roomList = Rooms();
        // Populate the roomList with available rooms
        // ...
        return roomList;
    }

    virtual RoomPrx createRoom(const string& name, const Ice::Current& current)
    {
        // Create a new room with the given name and return its proxy
        // ...
        return RoomPrx();
    }

    virtual RoomPrx findRoom(const string& name, const Ice::Current& current)
    {
        // Find the room with the given name and return its proxy
        // ...
        return RoomPrx();
    }

    virtual Users ListUsers(const Ice::Current& current)
    {
        auto userList = Users();
        // Populate the userList with available users
        // ...
        return userList;
    }

    virtual void RegisterRoomFactory(const RoomFactoryPrx& factory, const Ice::Current& current)
    {
        // Register the provided room factory
        // ...
    }

    virtual void UnregisterRoomFactory(const RoomFactoryPrx& factory, const Ice::Current& current)
    {
        // Unregister the provided room factory
        // ...
    }
};

int main(int argc, char* argv[])
{
    try
    {
        Ice::CommunicatorHolder ich(argc, argv);
        auto adapter = ich->createObjectAdapterWithEndpoints("ChatAdapter", "default -h localhost -p 10000");
        auto lobby = new LobbyI();

        // Register the lobby servant with the adapter
        adapter->add(lobby, Ice::stringToIdentity("Lobby"));

        adapter->activate();
        ich->waitForShutdown();
    }
    catch (const Ice::Exception& ex)
    {
        cerr << ex << endl;
        return 1;
    }

    return 0;
}

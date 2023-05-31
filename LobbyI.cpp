#include "LobbyI.h"

#include "RoomI.h"

void LobbyI::_cpp_register(const UserPrx& user, const std::string& password, const Ice::Current& current) {
    for (int i = 0; i < registeredUsers.size(); i++) {
        if (registeredUsers[i]->getName().compare(user->getName()) == 0) {
            throw Chat::UserExists();
        }
    }
    
    registeredUsers.push_back(user);

    std::cout << "User: " << user->getName() << " registered" << std::endl;
}

void LobbyI::login(const UserPrx& user, const std::string& password, const Ice::Current& current) {
    bool flag = false;
    for (int i = 0; i < registeredUsers.size(); i++) {
        if (registeredUsers[i]->getName().compare(user->getName()) == 0) {
            flag = true;
            break;
        }
    }
    if (flag) {
        loggedUsers.push_back(user);
        std::cout << "User: " << user->getName() << " logged in" << std::endl;
    }
}

void LobbyI::logout(const UserPrx& user, const Ice::Current& current) {
    for (int i = 0; i < loggedUsers.size(); i++) {
        if (loggedUsers[i]->getName().compare(user->getName()) == 0) {
            loggedUsers.erase(loggedUsers.begin() + i);
            return;
        }
    }
}

Rooms LobbyI::getRooms(const Ice::Current& current) {
    return rooms;
}

RoomPrx LobbyI::createRoom(const std::string& name, const Ice::Current& current) {
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getName().compare(name) == 0) {
            throw Chat::RoomExists{};
        }
    }

    RoomPtr servant = new RoomI(name);
    RoomPrx newRoom = RoomPrx::uncheckedCast(current.adapter->addWithUUID(servant));

    rooms.push_back(newRoom);
    return newRoom;
}

RoomPrx LobbyI::findRoom(const std::string& name, const Ice::Current& current) {
    for (int i = 0; i < rooms.size(); i++) {
        if (rooms[i]->getName().compare(name) == 0) {
            return rooms[i];
        }
    }

    throw Chat::NoSuchFactory();
}

Users LobbyI::ListUsers(const Ice::Current& current) {
    return registeredUsers;
}

void LobbyI::RegisterRoomFactory(const RoomFactoryPrx& factory, const Ice::Current& current) {
    // Register the provided room factory
    // ...
}

void LobbyI::UnregisterRoomFactory(const RoomFactoryPrx& factory, const Ice::Current& current) {
    // Unregister the provided room factory
    // ...
}

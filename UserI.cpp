#include "UserI.h"

UserI::UserI(const string& name) : name(name), status(UserStatus::Offline) {}

void UserI::sendMessage(const RoomPrx& room, const UserPrx& user, const string& message, const Ice::Current& current) {
    room->sendMessage(user, message);
}

void UserI::sendPrivateMessage(const UserPrx& user, const string& message, const Ice::Current& current) {
    user->receiveMessage(message);
}

void UserI::receiveMessage(const string& message, const Ice::Current& current) {
    std::cout << message << std::endl;
}

string UserI::getName(const Ice::Current& current) {
    return name;
}

UserStatus UserI::getStatus(const Ice::Current& current) {
    return status;
}

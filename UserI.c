#include "UserI.h"

void UserI::sendMessage(Room *room, User *user, string message, const Ice::Current &) {
    cout << "sendMessage()" << endl;
}

void UserI::sendPrivateMessage(User *user, string message, const Ice::Current &) {
    cout << "sendPrivateMessage()" << endl;
}

string UserI::getName(const Ice::Current &) {
    cout << "getName()" << endl;
    return "";
}

UserStatus UserI::getStatus(const Ice::Current &) {
    cout << "getStatus()" << endl;
    return UserStatus::BeBack;
}
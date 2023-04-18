#include "RoomI.h"

RoomI::RoomI() {
    cout << "RoomI()" << endl;
}
void RoomI::join(User *user, const Ice::Current &) {
    cout << "join()" << endl;
}

void RoomI::sendMessage(User *user, string message, const Ice::Current &) {
    cout << "sendMessage()" << endl;
}

void RoomI::leave(User *user, const Ice::Current &) {
    cout << "leave()" << endl;
}

Users RoomI::ListUsers(const Ice::Current &) {
    cout << "ListUsers" << std::endl;
    return Users();
}
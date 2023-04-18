#include "RoomI.h"

LobbyI::LobbyI() { std::cout << "Lobby!" << std::endl; }
void LobbyI::_cpp_register(User* user, string password, const Ice::Current&) {
    cout << "register()" << endl;
}

void LobbyI::login(User* user, string password, const Ice::Current&) {
    cout << "login()" << endl;
}

void LobbyI::logout(const Ice::Current&) {
    cout << "logout()" << endl;
}

Rooms LobbyI::getRooms(const Ice::Current&) {
    cout << "getRooms()" << endl;
    return Rooms();
}

Room* LobbyI::createRoom(string name, const Ice::Current&) {
    cout << "createRoom()" << endl;
    return RoomI();
}

Room* LobbyI::findRoom(string name, const Ice::Current&) {
    cout << "getRooms()" << endl;
    return RoomI();
}

Users LobbyI::ListUsers(const Ice::Current&) {
    cout << "ListUsers()" << endl;
    return Users();
}

void RegisterRoomFactory(RoomFactory* factory, const Ice::Current&) {
    cout << "getRooms()" << endl;
}

void UnregisterRoomFactory(RoomFactory* factory, const Ice::Current&) {
    cout << "getRooms()" << endl;
}

int main(int argc, char* argv[]) {
    int status = 0;
    Ice::CommunicatorPtr ic;
    try {
        ic = Ice::initialize(argc, argv);
        Ice::ObjectAdapterPtr adapter =
            ic->createObjectAdapterWithEndpoints("SimpleChat", "default -p 10000");
        Ice::ObjectPtr object = new LobbyI();
        adapter->add(object, ic->stringToIdentity("SimpleChat"));
        adapter->activate();
        ic->waitForShutdown();
    } catch (const Ice::Exception& e) {
        cerr << e << endl;
        status = 1;
    } catch (const char* msg) {
        cerr << msg << endl;
        status = 1;
    }
    if (ic) {
        try {
            ic->destroy();
        } catch (const Ice::Exception& e) {
            cerr << e << endl;
            status = 1;
        }
    }
    return status;
}
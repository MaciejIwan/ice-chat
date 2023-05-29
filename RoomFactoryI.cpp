#include "RoomFactoryI.h"

RoomFactoryI::RoomFactoryI(const LobbyPrx& lobby) : lobby(lobby) {}

RoomPrx RoomFactoryI::createRoom(const string& name, const Ice::Current& current) {
    try {
        return lobby->findRoom(name);
    } catch (const RoomExists&) {
        throw RoomExists();
    } catch (const AccessDenied&) {
        throw AccessDenied();
    }
}

double RoomFactoryI::getServerLoad(const Ice::Current& current) {
    // Provide an appropriate implementation for the server load calculation
    // For simplicity, return a constant value.
    return 0.5;
}

#include <Ice/Ice.h>

#include <memory>

#include "Chat.h"
#include "LobbyI.h"

using namespace std;
using namespace Chat;

int main(int argc, char* argv[]) {
    try {
        Ice::CommunicatorHolder ich(argc, argv);
        auto adapter = ich->createObjectAdapterWithEndpoints("ChatAdapter", "default -h localhost -p 10000");
        auto lobby = new LobbyI();

        // Register the lobby servant with the adapter
        adapter->add(lobby, Ice::stringToIdentity("Lobby"));

        adapter->activate();
        ich->waitForShutdown();
    } catch (const Ice::Exception& ex) {
        cerr << ex << endl;
        return 1;
    }

    // if (ich) {
    //     try {
    //         ich->destroy();
    //     } catch (const std::exception& e) {
    //         std::cerr << e.what() << '\n';
    //         return 1;
    //     }
    // }

    return 0;
}

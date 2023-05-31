#include <Ice/Ice.h>

#include <memory>

#include "Chat.h"
#include "LobbyI.h"

using namespace std;
using namespace Chat;

int main(int argc, char* argv[]) {
    int status = 0;
    Ice::CommunicatorPtr ic;
    try {
        ic = Ice::initialize(argc, argv);
        Ice::ObjectAdapterPtr adapter =
            ic->createObjectAdapterWithEndpoints("ChatAdapter", "default -h localhost -p 10000");
        auto lobby = new LobbyI();
        
        adapter->add(lobby, Ice::stringToIdentity("Lobby"));
        adapter->activate();
        ic->waitForShutdown();
    } catch (const Ice::Exception& ex) {
        cerr << ex << endl;
        return 1;
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

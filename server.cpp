#include <Ice/Ice.h>
#include <fstream>
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

        ifstream configFile("server_config.txt");
        string serverEndpoint;
        if (configFile.is_open()) {
            getline(configFile, serverEndpoint);
            cout << serverEndpoint << endl;

            configFile.close();
        } else {
            cerr << "Failed to open server configuration file." << endl;
            return 1;
        }

        Ice::ObjectAdapterPtr adapter =
            ic->createObjectAdapterWithEndpoints("ChatAdapter", serverEndpoint);
        auto lobby = new LobbyI();

        adapter->add(lobby, Ice::stringToIdentity("Lobby"));
        adapter->activate();
        cout << "server started!" << endl;
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

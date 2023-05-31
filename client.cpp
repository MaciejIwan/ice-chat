#include <csignal>
#include <fstream>
#include "RoomI.h"
#include "UserI.h"
using namespace std;
using namespace Chat;


int main(int argc, char const* argv[]) {
    int exitStatus = EXIT_SUCCESS;
    Ice::CommunicatorPtr ice;

    try {
        ice = Ice::initialize(argc, argv);

        ifstream configFile("client_config.txt");
        string serverEndpoint;
        if (configFile.is_open()) {
            getline(configFile, serverEndpoint);
            cout << serverEndpoint << endl;
            configFile.close();
        } else {
            cerr << "Failed to open client configuration file." << endl;
            return 1;
        }

        Ice::ObjectAdapterPtr adapter = ice->createObjectAdapterWithEndpoints("adapter2", "default");

        string name;
        cout << "Enter username: ";
        cin >> name;

        Ice::ObjectPtr objectUser = new UserI(name);
        Ice::ObjectPrx userPrxBase = adapter->addWithUUID(objectUser);
        adapter->activate();

        UserPrx userPrx = UserPrx::checkedCast(userPrxBase);

        Ice::ObjectPrx serverPrxBase = ice->stringToProxy(serverEndpoint);

        LobbyPrx serverPrx = LobbyPrx::checkedCast(serverPrxBase);
        if (!serverPrx) {
            throw "Invalid server proxy";
        }
        serverPrx->_cpp_register(userPrx, " ");
        serverPrx->login(userPrx, " ");

        bool end = false;
        while (!end) {
            fflush(stdin);
            cout << "---------- SignIn as: " << userPrx->getName() << " ------------" << endl;
            cout << "1 - send private message" << endl;
            cout << "2 - create a room" << endl;
            cout << "3 - join the room" << endl;
            cout << "4 - leave the room" << endl;
            cout << "5 - send message to the room" << endl;
            cout << "6 - exit" << endl;
            cout << "----------Rooms------------" << endl;
            for (int i = 0; i < serverPrx->getRooms().size(); i++) {
                std::cout << serverPrx->getRooms()[i]->getName() << std::endl;
            }
            int action;
            std::cout << "Type action: ";
            std::cin >> action;
            switch (action) {
                case 1: {  // send private message
                    char message[1024];
                    string username;
                    cout << "Receiver username: " << endl;
                    cin >> username;

                    cout << "Message: ";
                    cin.ignore();
                    cin.getline(message, 1024);

                    Users users = serverPrx->ListUsers();
                    for (int i = 0; i < users.size(); i++) {
                        if (users[i]->getName().compare(username) == 0) {
                            users[i]->receiveMessage(message);
                        }
                    }
                    break;
                }
                case 2: {
                    try {
                        string roomName;
                        cout << "Room name: ";
                        cin >> roomName;

                        RoomPrx proxy = serverPrx->createRoom(roomName);

                        cout << "Room created!!!" << endl;
                    } catch (RoomExists& e) {
                        cout << "Room already exist!" << endl;
                    }
                    break;
                }
                case 3: {
                    string roomName;
                    cout << "Room name: ";
                    cin >> roomName;

                    RoomPrx proxy = serverPrx->findRoom(roomName);
                    proxy->join(userPrx);

                    cout << "You joined " << proxy->getName() << endl;
                    break;
                }
                case 4: {
                    string roomName;
                    cout << "Room name: ";
                    cin >> roomName;

                    RoomPrx proxy = serverPrx->findRoom(roomName);

                    proxy->leave(userPrx);
                    cout << "you left the room!" << endl;

                    break;
                }
                case 5: {
                    char message[1024];
                    string roomName;
                    cout << "Room name: ";
                    cin >> roomName;

                    RoomPrx proxy = serverPrx->findRoom(roomName);

                    cout << "Message: ";
                    cin.ignore(1024, '\n');
                    cin.getline(message, 1024);

                    proxy->sendMessage(userPrx, message);
                    break;
                }
                case 6: {
                    serverPrx->logout(userPrx);
                    end = true;
                    std::cout << "Bye bye..." << std::endl;
                    break;
                }
                default:
                    cout << "Unknown action!!!" << endl;
                    break;
            }
        }
    } catch (UserExists& e) {
        cout << "User already exist" << endl;
        exitStatus = EXIT_FAILURE;
    } catch (const Ice::Exception& e) {
        std::cerr << e << '\n';
        exitStatus = EXIT_FAILURE;
    }
    if (ice) {
        try {
            ice->destroy();
        } catch (const std::exception& e) {
            cerr << e.what() << endl;
            exitStatus = EXIT_FAILURE;
        }
    }

    return exitStatus;
}

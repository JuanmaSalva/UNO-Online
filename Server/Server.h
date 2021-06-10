#include <iostream>
#include <vector>
#include <memory>

#include "../Common/SocketTCP.h"

class Server{
public:
    Server(const char*s, const char*p, int _numPlayers);

    void StartGame();

private:
    std::vector<std::unique_ptr<SocketTCP>> clients;

    SocketTCP socket;

    int connectedPlayers = 0;
    int numPlayers;

    void ConnectPlayer();
};
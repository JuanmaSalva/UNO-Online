#include <iostream>
#include <vector>
#include <memory>

#include "../Common/SocketTCP.h"

class Server{
public:
    Server(const char*s, const char*p);

    void StartGame(int numPlayers);

private:
    std::vector<std::unique_ptr<SocketTCP>> clients;

    SocketTCP socket;

    int connectedPlayers = 0;
};
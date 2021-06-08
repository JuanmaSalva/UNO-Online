#include <iostream>
#include <vector>
#include <memory>

#include "../Common/Socket.h"

class Server{
public:
    Server(const char*s, const char*p): socket(s, p)
    {
        std::cout << "Creando el servidor del Uno\n";
        socket.bind();
        socket.StartListen(16);
    };


    void StartGame(int numPlayers);

private:
    std::vector<std::unique_ptr<Socket>> clients;

    Socket socket;

    int connectedPlayers = 0;
};
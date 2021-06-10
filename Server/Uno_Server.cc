#include "Server.h"

#include <iostream>

//TCP Uno server
// ./uno_server <host ip> <host port> <number of players>
int main(int argc, char **argv) //argv[1] = direccion, argv[2] = puerto, argv[3] = jugadores
{
    if (argc < 4)
    {
        std::cerr << "Usage: uno_server <host ip> <host port> <number of players>\n";
        return 0;
    }

    Server server(argv[1], argv[2], atoi(argv[3]));

    server.StartGame();

    return 0;
}

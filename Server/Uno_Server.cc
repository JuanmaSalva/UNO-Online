#include "Server.h"

#include <iostream>

int main(int argc, char **argv) //argv[1] = direccion, argv[2] = puerto, argv[3] = jugadores 
{
    Server server(argv[1], argv[2]);

    server.StartGame(atoi(argv[3]));

    return 0;
}

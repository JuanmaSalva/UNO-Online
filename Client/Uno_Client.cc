#include "Client.h"

int main(int argc, char **argv) //argv[1] = direccion, argv[2] = puerto, argv[3] = nombre
{
    Client client(argv[1], argv[2], argv[3]);

    //client.StartGame();

    client.Close();
}
#include "Client.h"

//TCP Uno client
// ./uno_client <host server> <host port>
int main(int argc, char **argv) //argv[1] = direccion, argv[2] = puerto
{
    if(argc < 3){
        std::cerr << "Usage: uno_client <host server> <host port>\n";
        return 0;
    }
    Client client(argv[1], argv[2]);

    client.StartGame();
}
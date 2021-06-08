#include "Server.h"


Server::Server(const char*s, const char*p): socket(s,p)
{
    std::cout << "Creando el servidor del Uno\n";
};

void Server::StartGame(int numPlayers)
{
    //esperamos a recibir una llamada
    SocketTCP auxSock = socket.clientConnect();

    if(auxSock.recv() == 0){
        std::cout << "Cerramos\n";
    }

    //cerramos nuestra conexión
    socket.closeConnection();
}
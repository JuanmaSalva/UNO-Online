#include "Server.h"

Server::Server(const char *s, const char *p) : socket(s, p)
{
    std::cout << "Creando el servidor del Uno\n";
};

void Server::StartGame(int numPlayers)
{
    while (connectedPlayers < numPlayers)
    {
        //esperamos a recibir una llamada
        SocketTCP *auxSock = socket.clientConnect();

        std::unique_ptr<SocketTCP> aux(auxSock);
        clients.push_back(std::move(aux));

        connectedPlayers++;
        std::cout << "Jugadores restantes: " << connectedPlayers << "\n";
    }

    //cerramos nuestra conexión y la de todas las conexiones
    /*for(int i=0;i<clients.size();i++){
        SocketTCP indx = *clients[i].get(); 
        indx.closeConnection();
    }*/

    socket.closeConnection();
}
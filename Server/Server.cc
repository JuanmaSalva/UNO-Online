#include "Server.h"

void Server::StartGame(int numPlayers)
{
    std::cout << "Creando nueva partida para " << numPlayers << " jugadores\n";


    //esperamos a tener 4 jugadores esperando

    while(connectedPlayers < numPlayers){
        Socket *client;
        
        if(socket.clientConnect(client) != 0){
            std::cout << "Error en la conexión de un cliente\n";
            break;
        }

        //lo añadimos al vector de sockets
        std::unique_ptr<Socket> aux(client);
        clients.push_back(std::move(aux));

        connectedPlayers++;
        std::cout << "Jugadores restantes: " << numPlayers-connectedPlayers << "\n";
    }

    std::cout << "Partida llena, agarrate que esto empieza ya de ya\n";

}
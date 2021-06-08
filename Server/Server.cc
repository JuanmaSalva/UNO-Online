#include "Server.h"
#include "../Client/Chat.h"

void Server::StartGame(int numPlayers)
{
    std::cout << "Creando nueva partida para " << numPlayers << " jugadores\n";
    

    //esperamos a tener el numero de jugadores requeridos
    /*while(connectedPlayers < numPlayers){
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
    std::cout << "Partida llena, agarrate que esto empieza ya de ya\nVamos a enviar los datos\n";*/

    //recorremos todos los clientes y les mandamos un mensaje de que empiezxa el juego
    /*ChatMessage msg; //mensaje provisional
    for(int i=0;i<clients.size();i++){
        Socket indx = *clients[i].get(); 
        indx.sen(msg, indx);
    }*/

    socket.closeConection();
    std::cout << "Hemos avisado a todos\n";
}
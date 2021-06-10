#include "Server.h"
#include "../Common/Player.h"

Server::Server(const char *s, const char *p, int _numPlayers) : socket(s, p), numPlayers(_numPlayers)
{
    std::cout << "Creando el servidor del Uno\n";
    ConnectPlayer();
};

void Server::StartGame()
{
    Player msg;
    msg.type = Player::INFO;
    for(int i=0;i<clients.size();i++){
        SocketTCP indx = *clients[i].get(); 
        //les mandamos un mensaje a todos de que empieza el juego (antes de esto tenemos que asegurarnos de repartir las cartas)
        indx.send(msg);
    }

    while(true);
    

    socket.closeConnection();
}

void Server::ConnectPlayer(){
    while (connectedPlayers < numPlayers)
    {
        //esperamos a recibir una llamada
        SocketTCP *auxSock = socket.clientConnect();

        std::unique_ptr<SocketTCP> aux(auxSock);
        clients.push_back(std::move(aux));

        connectedPlayers++;
        std::cout << "Jugadores restantes: " << connectedPlayers << "\n";
    }
}
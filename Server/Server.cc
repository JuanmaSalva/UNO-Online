#include "Server.h"
#include <cstdlib> 
#include <algorithm>  

Server::Server(const char *s, const char *p, int _numPlayers) : socket(s, p), numPlayers(_numPlayers)
{
    std::cout << "Creando el servidor del Uno\n";
    ConnectPlayer();

	system("clear");
    std::cout << "Empieza la partida\n";
    InitCards();
};

void Server::StartGame()
{
    //repartimos las cartas a los jugadores
    DealCards();

    for(int i=0;i<clients.size();i++){
        SocketTCP indx = *clients[i].get(); 
        //les mandamos un mensaje a todos de que empieza el juego (antes de esto tenemos que asegurarnos de repartir las cartas)
        players[i].type = Player::INFO;
        players[i].setTopCard(topCard);
        indx.send(players[i]);
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
        players.push_back(Player());
        std::cout << "Jugadores restantes: " << connectedPlayers << "\n";
    }
}

void Server::InitCards(){
    //por colores
    for(int i=0;i<4;i++){
        //añadimos las 19 cartas de numeros (un 0 y del resto 2) y  2 de cada comodín
        cards.push_back(Card((Colors)i,Symbol::Zero));

        for(int j = 1; j < 13; j++){
            cards.push_back(Card((Colors)i,(Symbol)j));
            cards.push_back(Card((Colors)i,(Symbol)j));
        }

        //añadimos un comodín especial
        cards.push_back(Card(Colors::Wild,Symbol::Wild));
        cards.push_back(Card(Colors::Wild,Symbol::WildDrawFour));
    }    
}

void Server::DealCards(){
    srand(time(NULL)); //para no hacer todas las partidas iguales (cambia la seed)
    std::random_shuffle(cards.begin(), cards.end());    //mezclamos las cartas

    //pasamos las cartas desordenadas al monton
    for(int i=0;i<cards.size();i++){
        cardsPile.push(cards[i]);
    }

    //repartimos 7 cartas a cada uno, empezando por el primero que se ha conectado
    for(int i = 0;i<7;i++){
        for(int j=0;j<players.size();j++){
            players[j].addCard(cardsPile.front());
            cardsPile.pop();
        }
    }

    topCard = cardsPile.front();
    usedCardsPile.push(cardsPile.front());
    cardsPile.pop();
}
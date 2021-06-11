#include "Server.h"
#include <cstdlib>
#include <algorithm>
#include "../Common/Play.h"

Server::Server(const char *s, const char *p, int _numPlayers) : socket(s, p), numPlayers(_numPlayers)
{
    std::cout << "Creando el servidor del Uno\n";
    ConnectPlayers();

    system("clear");
    std::cout << "Empieza la partida\n";
    InitCards();
};

void Server::StartGame()
{
    //repartimos las cartas a los jugadores
    DealCards();
    SendInfo();

    while (inGame)
    {
        WaitPlayer();
        if (inGame)
            SendInfo(); //antes de mandarlo miramo si seguimos en el juego
    }

    socket.closeConnection();
}

void Server::ConnectPlayers()
{
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

void Server::InitCards()
{
    //por colores
    for (int i = 0; i < 4; i++)
    {
        //añadimos las 19 cartas de numeros (un 0 y del resto 2) y  2 de cada comodín
        cards.push_back(Card((Colors)i, Symbol::Zero));

        for (int j = 1; j < 13; j++)
        {
            cards.push_back(Card((Colors)i, (Symbol)j));
            cards.push_back(Card((Colors)i, (Symbol)j));
        }

        //añadimos un comodín especial
        cards.push_back(Card(Colors::Wild, Symbol::Wild));
        cards.push_back(Card(Colors::Wild, Symbol::WildDrawFour));
    }
}

void Server::DealCards()
{
    srand(time(NULL));                               //para no hacer todas las partidas iguales (cambia la seed)
    std::random_shuffle(cards.begin(), cards.end()); //mezclamos las cartas

    //pasamos las cartas desordenadas al monton
    for (int i = 0; i < cards.size(); i++)
    {
        cardsPile.push(cards[i]);
    }

    //repartimos 7 cartas a cada uno, empezando por el primero que se ha conectado
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < players.size(); j++)
        {
            players[j].addCard(cardsPile.front());
            cardsPile.pop();
        }
    }

    topCard = cardsPile.front();
    usedCardsPile.push(cardsPile.front());
    cardsPile.pop();
}

void Server::SendInfo()
{
    //manda un mensaje a todo el mundo de la información de la partida, y al que le toca el turno le manda un mensaje especial

    for (int i = 0; i < clients.size(); i++)
    {
        SocketTCP indx = *clients[i].get();
        //les mandamos un mensaje a todos de que empieza el juego (antes de esto tenemos que asegurarnos de repartir las cartas)
        if (i != playerTurn)
            players[i].type = Player::INFO;
        else
            players[i].type = Player::TURN;
        players[i].setTopCard(topCard);
        indx.send(players[i]);
    }
}

void Server::WaitPlayer()
{
    SocketTCP indx = *clients[playerTurn].get();
    Play play;

    if (indx.recv(play) == 0)
    {
        //terminamos el juego
        inGame = false;
    }
    else
    {
        std::cout << "Se ha jugado una carta \n";
        //le quitamos al jugador esa carta y la ponemos en el montón
        usedCardsPile.push(players[playerTurn].getCard(play.getCardPlayed()));
        topCard = usedCardsPile.back();
        usedCardsPile.back().print();
        players[playerTurn].playCard(play.getCardPlayed());
    }

    playerTurn++;
    playerTurn %= numPlayers;
}

void Server::EndGame()
{
    //les enviamos un mensaje a todos que hemos terminado la partida
    for (int i = 0; i < clients.size(); i++)
    {
        SocketTCP indx = *clients[i].get();
        players[i].type = Player::END;
        indx.send(players[i]);
    }
}
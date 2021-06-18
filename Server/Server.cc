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
	SendInfo(-1);

	while (inGame)
	{
		WaitPlayer();
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
		cards.push_back(Card((Colors)i, Symbols::Zero));

		for (int j = 1; j < 13; j++)
		{
			cards.push_back(Card((Colors)i, (Symbols)j));
			cards.push_back(Card((Colors)i, (Symbols)j));
		}

		//añadimos un comodín especial
		cards.push_back(Card(Colors::Wild, Symbols::Wild));
		cards.push_back(Card(Colors::Wild, Symbols::WildDrawFour));
	}
}

void Server::DealCards()
{
	srand(time(NULL));								 //para no hacer todas las partidas iguales (cambia la seed)
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

void Server::SendInfo(int lostTurn)
{
	//manda un mensaje a todo el mundo de la información de la partida, y al que le toca el turno le manda un mensaje especial
	std::cout << "Sending info\n";
	//std::cout << "player " << lostTurn << " lost their turn, it's player " << playerTurn << "'s turn\n";
	for (int i = 0; i < clients.size(); i++)
	{
		SocketTCP indx = *clients[i].get();
		//les mandamos un mensaje a todos de que empieza el juego (antes de esto tenemos que asegurarnos de repartir las cartas)
		if (i != playerTurn && i != lostTurn)
			players[i].type = Player::MessageType::INFO;
		else if (i == lostTurn) //Nos habiamos saltado el turno del jugador, hay que avisarle de ello
			players[i].type = Player::MessageType::LOST;
		else
			players[i].type = Player::MessageType::TURN;

		players[i].setTopCard(topCard);
		//std::cout << "sending " << i << " msg type " << (short)players[i].type << "\n";
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
		int lostIndex = -1;

		std::cout << "Se ha jugado una carta \n";
		if (play.getCardPlayed() == -1)
		{
			//El jugador ha robado carta
			giveCards(playerTurn, 1);
			playerTurn = nextPlayer();
		}
		else
		{
			Card playedCard = players[playerTurn].getCard(play.getCardPlayed());

			if (topCard.isValidMatchup(playedCard))
			{

				//le quitamos al jugador esa carta y la ponemos en el montón
				//si la carta es wild, la carta que añadimos al monton es de ese tipo pero con otro color
				usedCardsPile.push(playedCard);
				if (playedCard.getSymbol() == Symbols::Wild || playedCard.getSymbol() == Symbols::WildDrawFour)
				{
					topCard = Card(play.getChosenColor(), playedCard.getSymbol());
				}
				else
				{
					topCard = usedCardsPile.back();
				}

				topCard.print();
				players[playerTurn].playCard(play.getCardPlayed());

				switch (playedCard.getSymbol())
				{
				case Symbols::Reverse:
					//Invierte el orden de turnos
					ascendingOrder = !ascendingOrder;
					break;
				case Symbols::Skip:
					//Acabará avanzando el turno dos veces, saltando al jugador que iba siguiendo
					lostIndex = nextPlayer();
					playerTurn = nextPlayer();
					break;
				case Symbols::DrawTwo:
					giveCards(nextPlayer(), 2);
					lostIndex = nextPlayer();
					playerTurn = nextPlayer();
					break;
				case Symbols::WildDrawFour:
					giveCards(nextPlayer(), 4);
					lostIndex = nextPlayer();
					playerTurn = nextPlayer();
					break;
				default:
					break;
				}

				playerTurn = nextPlayer();
			}
			//Else implícito
			//El cliente debería manejar movimientos inválidos, por lo que si nos llega un movimiento inválido es por manipulación de mensajes
			//no hacemos ningun handling especial, volvemos a promptear a los clientes con el mismo mensaje y no avanzamos turno
		}
		SendInfo(lostIndex);
	}
}

void Server::EndGame()
{
	//les enviamos un mensaje a todos que hemos terminado la partida
	for (int i = 0; i < clients.size(); i++)
	{
		SocketTCP indx = *clients[i].get();
		players[i].type = Player::MessageType::END;
		indx.send(players[i]);
	}
}

int Server::nextPlayer()
{
	if (ascendingOrder)
	{
		return (playerTurn + 1) % numPlayers;
	}
	else
	{
		return (playerTurn == 0) ? numPlayers - 1 : playerTurn - 1;
	}
}

void Server::giveCards(int player, int numCards)
{
	//Dar cartas al jugador seleccionado de las disponibles en la pila de robar
	for (int i = 0; i < numCards; i++)
	{
		players[player].addCard(cardsPile.front());
		cardsPile.pop();

		//Si se acaba la pila de robar, cambiar las pilas
		if (cardsPile.empty())
		{
			cardsPile = usedCardsPile;
			usedCardsPile = std::queue<Card>();
		}
	}
}
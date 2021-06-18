#include "Client.h"
#include "../Common/Player.h"
#include "../Common/Play.h"

void Client::StartGame()
{
	//nos quedamos escuchando mensajes
	std::cout << "Esperando a que empiece el juego\n";

	while (inGame)
	{
		Player msg;
		if (socket.recv(msg) == 0)
		{
			inGame = false;
			continue;
		}

		switch (msg.type)
		{
		case Player::MessageType::START:
		{
			std::cout << "START\n";
			break;
		}
		case Player::MessageType::INFO:
		{
			std::cout << "INFO\n";
			msg.Print();
			break;
		}
		case Player::MessageType::TURN:
		{
			std::cout << "TURN\n";
			msg.Print();
			std::cout << "\nIt's your turn to play.\nSelect which card you want to play: ";
			Turn(msg);
			break;
		}
		case Player::MessageType::LOST:
		{
			std::cout << "SKIPPED\n";
			msg.Print();
			std::cout << "\nYour turn was skipped!\n";
			break;
		}
		case Player::MessageType::END:
		{
			std::cout << "END\n";
			inGame = false;
			break;
		}
		default:
			break;
		}
	}
}

void Client::Close()
{
	socket.closeConnection();
}

void Client::Turn(Player &gamestate)
{
	short c, colorchoice;
	Play play;
	Card topCard = gamestate.getTopCard();

	std::cin >> c;
	while(c <= 0 || c > gamestate.numCards || !gamestate.getCard(c-1).isValidMatchup(topCard)){
		std::cout << "Choice invalid, choose a card that matches color, symbol or play a wild card\n";
		std::cin >> c;
	}

	if (gamestate.getCard(c - 1).getSymbol() == Symbols::Wild || gamestate.getCard(c - 1).getSymbol() == Symbols::WildDrawFour)
	{
		//Preguntar al jugador a que color quiere cambiar
		do
		{
			std::cout << "What color do you want to change to? \n1. Red \n2. Yellow \n3. Green \n4. Blue\n";
			std::cin >> colorchoice;
		} while (colorchoice < 1 || colorchoice > 4);

		play = Play(c - 1, Colors(colorchoice - 1));
	}
	else
	{
		play = Play(c - 1, gamestate.getCard(c - 1).getColor());
	}

	socket.send(play);
}
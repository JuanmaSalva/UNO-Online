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
			break;
		}
		case Player::MessageType::INFO:
		{
			msg.Print();
			printUNO(msg.extraInfo);
			break;
		}
		case Player::MessageType::TURN:
		{
			msg.Print();
			printUNO(msg.extraInfo);
			std::cout << "\nIt's your turn to play.\nSelect which card you want to play: ";
			Turn(msg);
			break;
		}
		case Player::MessageType::LOST:
		{
			msg.Print();
			printUNO(msg.extraInfo);
			std::cout << "\nYour turn was skipped!\n";
			break;
		}
		case Player::MessageType::END:
		{
			system("clear");
			inGame = false;
			if (msg.extraInfo == 999)
			{
				std::cout << "You've won! Congratulations!\n";
			}
			else if (msg.extraInfo == -1)
			{
				std::cout << "Match ended abruptly.\n";
			}
			else
			{
				std::cout << "Player " << msg.extraInfo << " has won! Better luck next time!\n";
			}
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
	while (c < 0 || c > gamestate.numCards || (c != 0 && !gamestate.getCard(c - 1).isValidMatchup(topCard)))
	{
		std::cout << "Choice invalid, choose a card that matches color, symbol or play a wild card\n";
		std::cin >> c;
	}

	if (c == 0)
	{
		//El jugador quiere robar carta
		play = Play(-1, Colors::Wild);
	}
	else if (gamestate.getCard(c - 1).getSymbol() == Symbols::Wild || gamestate.getCard(c - 1).getSymbol() == Symbols::WildDrawFour)
	{
		//Preguntar al jugador a que color quiere cambiar
		do
		{
			std::cout << "What color do you want to change to? \n\033[0;31m1. Red \n\033[0;33m2. Yellow \n\033[0;32m3. Green \n\033[0;34m4. Blue\n\033[0;97m";
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

void Client::printUNO(short bitmask)
{
	if (bitmask != 0)
	{
		std::cout << "\nUNO! The following players are one card away from winning!\n";
		for (int i = 0; i < 8; i++)
		{
			if (bitmask % 2 == 1)
			{
				std::cout << "Player " << i << ".\n";
			}
			bitmask = bitmask >> 1;
		}
		std::cout << "\n";
	}
}

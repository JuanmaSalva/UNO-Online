#pragma once

#include "Cards.h"
#include "Serializable.h"

#include <string>
#include <ostream>

#define MAX_HAND_SIZE 30

class Player : public Serializable
{
protected:
	Card _playerHand[MAX_HAND_SIZE];
	Card _topCard;

public:
	Player();

	void to_bin();

	int from_bin(char *data);

	void addCard(Card c);

	void setTopCard(Card c);

	Card getTopCard() { return _topCard; }

	Card getCard(short i)
	{
		return _playerHand[i];
	}

	void playCard(short c);

	enum MessageType
	{
		START = 0, //empieza la partida
		INFO = 1,  //ha jugado otro juegador y se actualiza la carta que está arriba del mazo visible
		TURN = 2,  //nos toca a nosotros
		END = 3	   //se termina la partida
	};

	uint8_t type;
	short numCards = 0;

	void Print();
	void dumpCards();
};
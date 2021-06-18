#include "Player.h"

#include <iostream>

Player::Player()
{
	_size = (MAX_HAND_SIZE + 1) * sizeof(Card) + sizeof(short) * 3;
}

void Player::to_bin()
{
	alloc_data(size());

	memset(_data, 0, size());

	char *tmp = _data;

	Colors auxColor;
	Symbols auxSymbol;
	for (int i = 0; i < MAX_HAND_SIZE; i++)
	{
		//Color
		auxColor = _playerHand[i].getColor();
		memcpy(tmp, &auxColor, sizeof(Colors));
		tmp += sizeof(Colors);

		//Symbol
		auxSymbol = _playerHand[i].getSymbol();
		memcpy(tmp, &auxSymbol, sizeof(Symbols));
		tmp += sizeof(Symbols);
	}

	//Top card
	auxColor = _topCard.getColor();
	memcpy(tmp, &auxColor, sizeof(Colors));
	tmp += sizeof(Colors);

	auxSymbol = _topCard.getSymbol();
	memcpy(tmp, &auxSymbol, sizeof(Symbols));
	tmp += sizeof(Symbols);

	//numero de cartas
	memcpy(tmp, &numCards, sizeof(short));
	tmp += sizeof(short);

	//tipo de mensaje
	memcpy(tmp, &type, sizeof(MessageType));
	tmp += sizeof(MessageType);

	//Valor auxiliar de mensaje
	memcpy(tmp, &extraInfo, sizeof(extraInfo));
	tmp += sizeof(extraInfo);
}

int Player::from_bin(char *data)
{
	alloc_data(size());

	memcpy(static_cast<void *>(_data), data, size());

	char *tmp = _data;

	Colors auxColor;
	Symbols auxSymbol;
	for (int i = 0; i < MAX_HAND_SIZE; i++)
	{
		//Color
		memcpy(&auxColor, tmp, sizeof(Colors));
		tmp += sizeof(Colors);

		//Symbol
		memcpy(&auxSymbol, tmp, sizeof(Symbols));
		tmp += sizeof(Symbols);

		_playerHand[i] = Card(auxColor, auxSymbol);
	}

	//Top card
	memcpy(&auxColor, tmp, sizeof(Colors));
	tmp += sizeof(Colors);

	//Symbol
	memcpy(&auxSymbol, tmp, sizeof(Symbols));
	tmp += sizeof(Symbols);

	_topCard = Card(auxColor, auxSymbol);

	//numero de cartas
	memcpy(&numCards, tmp, sizeof(short));
	tmp += sizeof(short);

	//tipo de mensaje
	memcpy(&type, tmp, sizeof(MessageType));
	tmp += sizeof(MessageType);

	//Valor auxiliar de mensaje
	memcpy(&extraInfo, tmp, sizeof(extraInfo));
	tmp += sizeof(extraInfo);

	return 0;
}

void Player::Print()
{
	system("clear");

	std::cout << "Top card on the pile: ";
	_topCard.print();
	std::cout << std::endl;

	std::cout << "\nYour cards are:\n";
	for (int i = 0; i < numCards; i++)
	{
		std::cout << i + 1 << ". ";
		_playerHand[i].print();
		std::cout << std::endl;
	}
	std::cout << "0. Draw card" << std::endl;;
}

void Player::addCard(Card c)
{
	_playerHand[numCards] = c;
	numCards++;
}

void Player::setTopCard(Card c)
{
	_topCard = c;
}

void Player::playCard(short c)
{
	//movemos todas las cartas desde c una posicion a la izquierda
	for (int i = c; i < numCards; i++)
	{
		_playerHand[i] = _playerHand[i + 1];
	}

	numCards--;
}

void Player::dumpCards()
{
	for (int i = 0; i < numCards; i++)
	{
		std::cout << i << ": ";
		//_playerHand[i].print();
		getCard(i).print();
		std::cout << "\n";
	}
}
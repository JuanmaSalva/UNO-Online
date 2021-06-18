#include "Player.h"

#include <iostream>

Player::Player()
{
	_size = (MAX_HAND_SIZE + 1) * sizeof(Card) + sizeof(uint8_t) * 3;
}

void Player::to_bin()
{
	alloc_data(size());

	memset(_data, 0, size());

	char *tmp = _data;

	Colors auxColor;
	Symbol auxSymbol;
	for (int i = 0; i < MAX_HAND_SIZE; i++)
	{
		//Color
		auxColor = _playerHand[i].getColor();
		memcpy(tmp, &auxColor, sizeof(Colors));
		tmp += sizeof(Colors);

		//Symbol
		auxSymbol = _playerHand[i].getSymbol();
		memcpy(tmp, &auxSymbol, sizeof(Symbol));
		tmp += sizeof(Symbol);
	}

	//Top card
	auxColor = _topCard.getColor();
	memcpy(tmp, &auxColor, sizeof(Colors));
	tmp += sizeof(Colors);

	auxSymbol = _topCard.getSymbol();
	memcpy(tmp, &auxSymbol, sizeof(Symbol));
	tmp += sizeof(Symbol);

	//msg type
	memcpy(tmp, &type, sizeof(uint8_t));
	tmp += sizeof(uint8_t);

	//number of cards
	memcpy(tmp, &numCards, sizeof(uint8_t));
	tmp += sizeof(uint8_t);

	
}


int Player::from_bin(char *data)
{
	alloc_data(size());

	memcpy(static_cast<void *>(_data), data, size());

	char *tmp = _data;

	Colors auxColor;
	Symbol auxSymbol;
	for (int i = 0; i < MAX_HAND_SIZE; i++)
	{
		//Color
		memcpy(&auxColor, tmp, sizeof(Colors));
		tmp += sizeof(Colors);

		//Symbol
		memcpy(&auxSymbol, tmp, sizeof(Symbol));
		tmp += sizeof(Symbol);

		_playerHand[i] = Card(auxColor, auxSymbol);
	}

	//Top card
	memcpy(&auxColor, tmp, sizeof(Colors));
	tmp += sizeof(Colors);

	//Symbol
	memcpy(&auxSymbol, tmp, sizeof(Symbol));
	tmp += sizeof(Symbol);

	_topCard = Card(auxColor, auxSymbol);

	//msg type
	memcpy(&type, tmp, sizeof(uint8_t));
	tmp += sizeof(uint8_t);

	//number of cards
	memcpy(&numCards, tmp, sizeof(uint8_t));
	tmp += sizeof(uint8_t);

	return 0;
}


void Player::Print()
{
	system("clear");

	std::cout << "Top card on the pile: ";
	_topCard.Print();

	std::cout << "\nYour cards are:\n";
	for(int i=0; i<numCards;i++){
		_playerHand[i].Print();
	}
}

void Player::addCard(Card c){
	_playerHand[numCards] = c;
	numCards++;
}

void Player::setTopCard(Card c){
	_topCard = c;
}

void Player::playCard(uint8_t c){
	//movemos todas las cartas desde c una posicion a la izquierda
	for(int i = c; i<numCards; i++){
		_playerHand[i] = _playerHand[i+1];
	}
	
	numCards--;
}
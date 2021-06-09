#include "Player.h"

Player::Player()
{
	_size = (MAX_HAND_SIZE + 1) * sizeof(Card);
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

	return 0;
}
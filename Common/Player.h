#pragma once

#include "Cards.h"
#include "Serializable.h"

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
};
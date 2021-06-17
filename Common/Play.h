#pragma once

#include "Serializable.h"
#include "Cards.h"

#include <string>
#include <ostream>

class Play : public Serializable
{
protected:
    short cardPlayed;
	Colors chosenColor;
public:
    Play():Play(0, Colors::Wild){};
	Play(short card, Colors color);

	void to_bin();

	int from_bin(char *data);

	short getCardPlayed(){
		return cardPlayed;
	}

	Colors getChosenColor(){
		return chosenColor;
	}
};
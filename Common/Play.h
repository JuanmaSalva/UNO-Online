#pragma once

#include "Serializable.h"

#include <string>
#include <ostream>

class Play : public Serializable
{
protected:
    uint8_t cardPlayed;

public:
    Play():Play(0){};
	Play(uint8_t card);

	void to_bin();

	int from_bin(char *data);
};
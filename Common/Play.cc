#include "Play.h"

Play::Play(short card, Colors color){
	_size = sizeof(short) + sizeof(Colors);
    cardPlayed = card;
	chosenColor = color;
}

void Play::to_bin()
{
	alloc_data(size());

	memset(_data, 0, size());

	char *tmp = _data;

	memcpy(tmp, &cardPlayed, sizeof(cardPlayed));
	tmp += sizeof(cardPlayed);

	memcpy(tmp, &chosenColor, sizeof(Colors));
	tmp += sizeof(Colors);
}

int Play::from_bin(char *data)
{
	alloc_data(size());

	memcpy(static_cast<void *>(_data), data, size());

	char *tmp = _data;

	memcpy(&cardPlayed, tmp, sizeof(cardPlayed));
	tmp += sizeof(cardPlayed);

	memcpy(&chosenColor, tmp, sizeof(Colors));
	tmp += sizeof(Colors);

    return 0;
}
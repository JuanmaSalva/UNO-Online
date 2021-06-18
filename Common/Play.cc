#include "Play.h"

Play::Play(uint8_t card)
{
	_size = sizeof(uint8_t);
	cardPlayed = card;
}

void Play::to_bin()
{
	alloc_data(size());

	memset(_data, 0, size());

	char *tmp = _data;

	memcpy(tmp, &cardPlayed, sizeof(uint8_t));
	tmp += sizeof(uint8_t);
}

int Play::from_bin(char *data)
{
	alloc_data(size());

	memcpy(static_cast<void *>(_data), data, size());

	char *tmp = _data;

	memcpy(&cardPlayed, tmp, sizeof(cardPlayed));
	tmp += sizeof(cardPlayed);

	return 0;
}
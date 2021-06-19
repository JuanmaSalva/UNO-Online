#include <iostream>

#include "../Common/SocketTCP.h"
class Player;

class Client
{
public:
	Client(const char *s, const char *p, const char *n) : socket(s, p, true)
	{
		//estamos ya conectados con el juego
	}

	void StartGame();

	void Close();
	void Turn(Player &gamestate);

private:
	SocketTCP socket;

	std::string nombre;

	bool inGame = true;
};
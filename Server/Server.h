#include <iostream>
#include <vector>
#include <queue>
#include <memory>

#include "../Common/SocketTCP.h"
#include "../Common/Player.h"
#include "../Common/Cards.h"

class Server
{
public:
	Server(const char *s, const char *p, int _numPlayers);

	void StartGame();
	void EndGame();

private:
	std::vector<std::unique_ptr<SocketTCP>> clients;
	std::vector<Player> players;
	std::vector<Card> cards; //vector que contiene todas las cartas

	std::queue<Card> cardsPile;
	std::queue<Card> usedCardsPile;

	Card topCard;

	SocketTCP socket;

	int connectedPlayers = 0;
	int numPlayers;

	int playerTurn = 0; //empieza jugando el jugador 0

	bool inGame = true;

	void InitCards();
	void ConnectPlayers();
	void DealCards();

	void SendInfo();
	void WaitPlayer();
};
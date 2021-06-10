#include <iostream>
#include <vector>
#include <queue>
#include <memory>

#include "../Common/SocketTCP.h"
#include "../Common/Player.h"
#include "../Common/Cards.h"

class Server{
public:
    Server(const char*s, const char*p, int _numPlayers);

    void StartGame();

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

    void InitCards();
    void ConnectPlayer();
    void DealCards();
};
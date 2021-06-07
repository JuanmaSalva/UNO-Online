#include <iostream>

#include "../Common/Socket.h"

class Client{
public:
    Client(const char * s, const char * p, const char * n):socket(s, p, true)
    {
        //estamos ya conectados con el juego
    }

    void StartGame();

    void Close();

private:
    Socket socket;

    std::string nombre;
};
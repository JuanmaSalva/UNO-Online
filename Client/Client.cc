#include "Client.h"
#include "Chat.h"

void Client::StartGame()
{
    //nos quedamos esperando en el recv a que nos digan que empiece el juego
    std::cout << "Estamos a la espera\n";
    ChatMessage msg;
    //Socket *auxSock = &socket;
    //while(socket.receive(msg, auxSock) != 0);
    //std::cout << "El juego va a empezar\n";
}

void Client::Close(){
    socket.closeConnection();
}
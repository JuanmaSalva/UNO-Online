#include "Client.h"
#include "Chat.h"

void Client::StartGame()
{
    //while(socket.recv() != 0);
}

void Client::Close(){
    socket.closeConnection();
}
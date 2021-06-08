#include "Client.h"
#include "Chat.h"

void Client::StartGame()
{
    while(socket.recv() != 0);

    std::cout << "Nos han cerrado la conexión\n";

    //Close();
}

void Client::Close(){
    socket.closeConnection();
}
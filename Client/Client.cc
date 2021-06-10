#include "Client.h"
#include "../Common/Player.h"

void Client::StartGame()
{
    //nos quedamos escuchando mensajes
    std::cout << "Esperando a que empiece el juego\n";

    while (inGame){
        Player msg;
        socket.recv(msg);

        switch (msg.type)
        {
            case 0:
                {
                    std::cout << "START\n";
                    break;
                }
            case 1:
                {
                    std::cout << "INFO\n";
                    msg.Print();
                    break;
                }
            case 2:
                {
                    std::cout << "TURN\n";
                    msg.Print();
                    break;
                }
            case 3:
                {
                    std::cout << "END\n";
                    inGame = false;
                    break;
                }
            default:
                break;
        }
    }
}

void Client::Close(){
    socket.closeConnection();
}
#include "Client.h"
#include "../Common/Player.h"
#include "../Common/Play.h"

void Client::StartGame()
{
    //nos quedamos escuchando mensajes
    std::cout << "Esperando a que empiece el juego\n";

    while (inGame){
        Player msg;
        if(socket.recv(msg) == 0) 
        {
            inGame = false;
            continue;
        }
        
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
                    std::cout << "\nIt's your turn to play. Select which card you want to play\n";
                    Turn();
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

void Client::Turn(){
    uint8_t c;
    std::cin >> c;
    
    Play play = Play(c-1);
    socket.send(play);
}
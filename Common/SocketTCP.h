#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

#include <iostream>
#include <stdexcept>
#include <string.h>

#include <ostream>

class SocketTCP;
class Serializable;

bool operator == (const SocketTCP &s1, const SocketTCP &s2);
std::ostream& operator << (std::ostream& os, const SocketTCP& dt);

class SocketTCP
{
public:
    static const int32_t MAX_MESSAGE_SIZE = 32000; //aprox xd

    //constructora para el server
    SocketTCP(const char *address, const char *port, bool isClient = false);

    SocketTCP(struct sockaddr _sa, socklen_t _sa_len, int newSd);

    SocketTCP *clientConnect();

    void closeConnection();

    int recv(Serializable &obj);

    int send(Serializable &obj);

    friend std::ostream& operator<<(std::ostream& os, const SocketTCP& dt);

    friend bool operator== (const SocketTCP &s1, const SocketTCP &s2);


private:
    int sd;

    struct sockaddr sa;
    socklen_t sa_len;
};
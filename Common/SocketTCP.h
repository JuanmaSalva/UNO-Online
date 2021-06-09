#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

#include <iostream>
#include <stdexcept>
#include <string.h>

#include <ostream>

class Socket;
class Serializable;


class SocketTCP{
public:
    //constructora para el server
    SocketTCP(const char * address, const char * port, bool isClient = false);

    SocketTCP(struct sockaddr _sa, socklen_t _sa_len, int newSd);

    SocketTCP* clientConnect();

    void closeConnection();

    int recv();

private: 
    int sd;

    struct sockaddr sa;
    socklen_t       sa_len;
};
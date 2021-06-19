#include "SocketTCP.h"
#include "Serializable.h"
#include <errno.h>

SocketTCP::SocketTCP(const char *address, const char *port, bool isClient)
{
    struct addrinfo hintsInfo;
    struct addrinfo *resInfo, *rp;

    memset((void *)&hintsInfo, 0, sizeof(struct addrinfo));

    hintsInfo.ai_family = AF_INET;       //le decimos que tiene que ser ipv4
    hintsInfo.ai_socktype = SOCK_STREAM; //tcp

    //hacemos la llamada por red
    int info = getaddrinfo(address, port, &hintsInfo, &resInfo);

    if (info != 0)
    { //error
        std::cout << "[getaddrinfo] error: " << gai_strerror(info) << "\n";
        return;
    }

    if (isClient)
    {
        //de toda la indormacion que nos da getaddrinfo, buscamos cual es la que queremos
        for (rp = resInfo; rp != NULL; rp = rp->ai_next)
        {
            sd = socket(rp->ai_family, rp->ai_socktype, 0); //creamos un socket

            if (sd == -1)
                continue;
            if (connect(sd, rp->ai_addr, rp->ai_addrlen) != -1)
                break;

            close(sd); //no deberiamos llegar aquí
        }
    }
    else
    {
        //en res[0] tenemos la direccion traducida a binario y el puerto
        sd = socket(resInfo->ai_family, resInfo->ai_socktype, 0); //creamos un socket

        //Nos aseguramos de poder rehostear en la misma IP
        int option = 1;
        if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) != 0){
            std::cerr << "[setsockopt] error: " << strerror(errno) << "\n";
            return;
        }

        if (sd == -1)
        {
            std::cerr << "[socket] error: " << strerror(errno) << "\n";
            return;
        }

        //hacemos el bind para asignarle una direccion al socket que acabamos de crear
        info = bind(sd, resInfo->ai_addr, resInfo->ai_addrlen);

        if (info != 0)
        {
            std::cerr << "[bind] error: " << strerror(errno) << "\n";
            return;
        }

        if (listen(sd, 16) != 0) //16 conexiones posibles
        {
            std::cerr << "[listen] error: " << strerror(errno) << "\n";
            return;
        }
    }

    freeaddrinfo(resInfo);

    sa = *resInfo->ai_addr;
    sa_len = resInfo->ai_addrlen;
}

SocketTCP::SocketTCP(struct sockaddr _sa, socklen_t _sa_len, int newSd) : sa(_sa), sa_len(_sa_len)
{
    sd = newSd;
}

void SocketTCP::closeConnection()
{
    close(sd);
}

SocketTCP *SocketTCP::clientConnect(std::string ipDest)
{
    char service[NI_MAXSERV];
    char host[NI_MAXHOST];

    struct sockaddr client;
    socklen_t client_len = sizeof(struct sockaddr);
    int client_socket;

    do{
        client_socket = accept(sd, &client, &client_len); //este es el socket q específico a esa conexión

        if(client_socket < 0){
            std::cerr << "[client connect] error: " << strerror(errno) << "\n";
            return nullptr;
        }

        getnameinfo(&client, client_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
        std::cout << "Connection from: " << host << ":" << service << "\n";
    } while (ipDest != "0" && strcmp(ipDest.c_str(), host) != 0);

    std::cout << ipDest.c_str() << " " << host << "\n";
    return new SocketTCP(client, client_len, client_socket);
}


int SocketTCP::recv(Serializable &obj)
{
    char buffer[MAX_MESSAGE_SIZE];
    ssize_t bytes = ::recv(sd, buffer, sizeof(buffer), 0);

    if(bytes < 0){
        std::cerr << "[recv] error: " << strerror(errno) << "\n";
    }

    if(bytes == 0)
        std::cout << "Se ha cerrado la conexión\n";
    else 
        obj.from_bin(buffer);

    //std::cout << "Mensaje recibido\n";
    return bytes;
}

int SocketTCP::send(Serializable &obj)
{
    obj.to_bin();

    int bytes = ::send(sd, obj.data(), obj.size(), 0);

    if(bytes < 0 )
        std::cerr << "[send] error: " << strerror(errno) << "\n";
    
    return bytes;
}

bool operator == (const SocketTCP &s1, const SocketTCP &s2)
{
    //en memoria un sockaddr_in es lo mismo que un sockaddr
    const struct sockaddr_in* a = (const struct sockaddr_in*)&s1.sa;
    const struct sockaddr_in* b = (const struct sockaddr_in*)&s2.sa;

    //Complos campos sin_family, sin_addr.s_addr y sin_port
    //de la estructura sockaddr_in de los Sockets s1 y s2
    //Retornar falarar se si alguno difiere
    if(a->sin_family == b->sin_family && a->sin_addr.s_addr == b->sin_addr.s_addr && a->sin_port == b->sin_port)
     return true;
    else return false;
};

std::ostream& operator<<(std::ostream& os, const SocketTCP& dt)
{
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    getnameinfo((struct sockaddr *) &(dt.sa), dt.sa_len, host, NI_MAXHOST, serv,
                NI_MAXSERV, NI_NUMERICHOST);

    os << host << ":" << serv;

    return os;
};

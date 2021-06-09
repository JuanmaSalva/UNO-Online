#include "SocketTCP.h"

SocketTCP::SocketTCP(const char * address, const char * port, bool isClient){
    struct addrinfo hintsInfo;
    struct addrinfo * resInfo, * rp;

    memset((void*) &hintsInfo, 0, sizeof(struct addrinfo));

    hintsInfo.ai_family = AF_INET; //le decimos que tiene que ser ipv4
    hintsInfo.ai_socktype = SOCK_STREAM; //tcp

    //hacemos la llamada por red
    int info = getaddrinfo(address, port, &hintsInfo, &resInfo);

    if(info != 0)
    { //error
        std::cout << "Se ha producido un error\n";
        return;
    }


    if(isClient){
        //de toda la indormacion que nos da getaddrinfo, buscamos cual es la que queremos
        for(rp = resInfo; rp != NULL; rp = rp->ai_next){
        sd = socket(rp->ai_family, rp->ai_socktype, 0); //creamos un socket
        
        if(sd == -1) 
            continue;
        if(connect(sd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;

        close(sd); //no deberiamos llegar aquí
    }
    }
    else {
        //en res[0] tenemos la direccion traducida a binario y el puerto    
        sd = socket(resInfo->ai_family, resInfo->ai_socktype, 0); //creamos un socket
        if(sd == -1){
            std::cout << "Se ha producido un error al crear el socket\n";
            return;
        }

        //hacemos el bind para asignarle una direccion al socket que acabamos de crear
        bind(sd, resInfo->ai_addr, resInfo->ai_addrlen);

        listen(sd, 16); //16 concexiones posibles
    }


    freeaddrinfo(resInfo);

    sa = *resInfo->ai_addr;
    sa_len = resInfo->ai_addrlen;
}

SocketTCP::SocketTCP(struct sockaddr _sa, socklen_t _sa_len, int newSd): sa(_sa), sa_len(_sa_len){
    sd = newSd;
}

void SocketTCP::closeConnection(){
    close(sd);
}

SocketTCP* SocketTCP::clientConnect(){
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];


    struct sockaddr client;
    socklen_t client_len = sizeof(struct sockaddr);
    int client_socket = accept(sd, &client, &client_len); //este es el socket q específico a esa conexión

    getnameinfo(&client, client_len, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
    std::cout << "Conexión desde: " << host << ":" << service << "\n";

    return new SocketTCP(client, client_len, client_socket);
}

int SocketTCP::recv(){
    char buffer[50];
    return ::recv(sd,buffer, 50, 0);
}
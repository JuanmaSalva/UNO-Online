CC=g++
CFLAGS=-g -I. -std=c++11
DEPS = Server/Server.h Client/Client.h Client/Chat.h Common/SocketTCP.h
OBJ = Server/Server.o Client/Client.o Client/Chat.o Common/SocketTCP.o
LIBS=-lpthread

%.o: %.cc $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

all: uno_server uno_client

uno_server: $(OBJ) Server/Uno_Server.o
	g++ -o Server/$@ $^ $(CFLAGS) $(LIBS)
	mv Server/$@ ./

uno_client: $(OBJ) Client/Uno_Client.o
	g++ -o Client/$@ $^ $(CFLAGS) $(LIBS)
	mv Client/$@ ./


.PHONY: clean

clean:
	rm -f uno_server uno_client
	rm -f Client/*.o Server/*.o Common/*.o


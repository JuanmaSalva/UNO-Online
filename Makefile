CC=g++
CFLAGS=-g -I. -std=c++11
DEPS = Common/Socket.h Server/Server.h Client/Client.h Client/Chat.h
OBJ = Common/Socket.o Server/Server.o Client/Client.o Client/Chat.o
LIBS=-lpthread

%.o: %.cc $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

all: uno_server uno_client

uno_server: $(OBJ) Server/Uno_Server.o
	g++ -o Server/$@ $^ $(CFLAGS) $(LIBS)

uno_client: $(OBJ) Client/Uno_Client.o
	g++ -o Client/$@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f *.o cs cc


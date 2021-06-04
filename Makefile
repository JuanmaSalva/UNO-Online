CC=g++
CFLAGS=-g -I. -std=c++11
DEPS = Common/Socket.h Client/Chat.h
OBJ = Common/Socket.o Client/Chat.o
LIBS=-lpthread

%.o: %.cc $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

all: cs cc

cs: $(OBJ) Server/ChatServer.o
	g++ -o Server/$@ $^ $(CFLAGS) $(LIBS)

cc: $(OBJ) Client/ChatClient.o
	g++ -o Client/$@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f *.o cs cc


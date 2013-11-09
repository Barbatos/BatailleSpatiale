CC=g++
EXEC=network-players
LDFLAGS=-lsfml-system -lsfml-network
CFLAGS =-Wall -std=c++11 -std=gnu++11

all: $(EXEC)

network-players: network-players.o ../../core/ReseauGlobal.o ../../core/ReseauClient.o ../../serveur/joueurs/Joueur.o ../../core/ReseauServer.o 
	$(CC) $^ $(LDFLAGS) -o $(CHEMIN_EXE)$@
	
%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@ 
	
.PHONY: clean 

clean:
	@rm -rf *.o
	
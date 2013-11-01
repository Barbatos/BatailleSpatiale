CC=g++
EXEC=network-players
LDFLAGS=-lsfml-system -lsfml-network
CFLAGS =-Wall 

all: $(EXEC)

network-players: network-players.o ../../core/NetworkGlobal.o ../../core/NetworkClient.o ../../serveur/joueurs/Joueur.o ../../core/NetworkServer.o 
	$(CC) $^ $(LDFLAGS) -o $(CHEMIN_EXE)$@
	
%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@ 
	
.PHONY: clean 

clean:
	@rm -rf *.o
	
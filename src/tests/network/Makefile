CC=g++
EXEC=network-client
LDFLAGS=-lsfml-system -lsfml-network
CFLAGS=-Wall -std=c++11 -std=gnu++11

all: $(EXEC)

network-client: network-client.o ../../commun/ReseauGlobal.o ../../commun/ReseauClient.o ../../serveur/joueurs/Joueur.o 
	$(CC) $^ $(LDFLAGS) -o $(CHEMIN_EXE)$@
	
%.o: %.cpp
	$(CC) $< $(CFLAGS) -c -o $@ 

.PHONY: clean 

clean:
	@rm -rf *.o
	
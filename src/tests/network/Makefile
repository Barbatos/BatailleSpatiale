CC=g++
EXEC=network-test
LDFLAGS=-lsfml-system -lsfml-network
CFLAGS =-Wall 

all: $(EXEC)

network-test: network-test.o ../../core/NetworkGlobal.o ../../core/NetworkClient.o ../../core/NetworkServer.o
	$(CC) $^ $(LDFLAGS) -o $(CHEMIN_EXE)$@
	
%.o: %.c
	$(CC) $< $(CFLAGS) -c -o $@ 
	
.PHONY: clean 

clean:
	@rm -rf *.o
	
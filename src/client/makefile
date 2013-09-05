CC= g++

#Les flags de compilation ( Debug, Optimisation )
CPPFLAGS= -g3 -o2 -Wall -Wextra

#Librairies ( SFML )
LDLIBS= -lsfml-graphics -lsfml-window -lsfml-system

#Flags de compilation
LDFLAGS= -I"C:\Program Files (x86)\SFML\include" -L"C:\Program Files (x86)\SFML\lib" -mwindows -lwsock32

#Le nom de l'éxecutable
EXE= Bin/Affichage.exe

# Commande de compilation
define COMPILER       
	@echo Compilation de $^
	@$(Q)$(CC) $(CPPFLAGS) -o $@ -c $< $(LDFLAGS)
endef

#Objets
FICHIERS_OBJ = 					\
	main.o						\
	Vue/Vue.o					\
	Vue/VueGraphique.o			\
	Affichage/Affichage.o		\
	Evenements/Evenements.o		\
	Ressources/Ressources.o		\
	Etats/Etats/Etat.o			\
	Etats/Etats/MenuPrincipal.o \
	Etats/Gestionnaire.o
	
#Si make : On compile
all: $(FICHIERS_OBJ)
	@echo Compilation de $(EXE)
	@g++ $(CPPFLAGS) $(FICHIERS_OBJ) -o $(EXE) $(LDFLAGS) $(LDLIBS)

#Si make exec : On éxecute
exec:
	./$(EXE)
	
%.o: %.cpp
	$(COMPILER)

#Si make clean : On clean les .o
clean:

.PHONY:
	clean

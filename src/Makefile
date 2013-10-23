# Fichier de compilation pour le jeu de Bataille Spatiale
# A compléter au fur et à mesure

# Détection de la plateforme sur laquelle on compile
ifndef PLATEFORME_COMPILATION
PLATEFORME_COMPILATION=$(shell uname|sed -e s/_.*//|tr '[:upper:]' '[:lower:]')
endif

# Détection de l'architecture
ifndef ARCHITECTURE_COMPILATION
ARCHITECTURE_COMPILATION=$(shell uname -m | sed -e s/i.86/i386/)
endif

# Si la plateforme est mingw et que l'architecture est 32bit, on renomme i386 en x86
# pour éviter les problèmes avec mingw.
ifeq ($(PLATEFORME_COMPILATION),mingw32)
  	ifeq ($(ARCHITECTURE_COMPILATION),i386)
    	ARCHITECTURE_COMPILATION=x86
  	endif
endif

# Version du programme
ifndef VERSION 
VERSION=0.1.1
endif

# Mode débug
ifndef DEBUG 
DEBUG=1
endif

# Compilateur à utiliser, par défaut g++
CC=g++

# Nom de l'exécutable client
ifndef EXECUTABLE_CLIENT
EXECUTABLE_CLIENT=BatailleSpatiale
endif

#Nom de l'exécutable serveur
ifndef EXECUTABLE_SERVEUR 
EXECUTABLE_SERVEUR=Serveur
endif

# Doit-on compiler le client ?
ifndef COMPILER_CLIENT
COMPILER_CLIENT=1
endif

# Doit-on compiler le serveur ?
ifndef COMPILER_SERVER 
COMPILER_SERVEUR=1
endif

# Activation de l'optimisation
ifndef OPTIMISER
OPTIMISER=0
endif

# Liste des optimisations à effectuer si OPTIMISER=1
OPTIMISATIONS = -03

# Répertoire où seront les différents fichiers lors de la compilation
ifndef REP_BUILD
REP_BUILD=build
endif

# Répertoire où seront les fichiers DEBUG
ifndef REP_DEBUG
REP_DEBUG=$(REP_BUILD)/debug-$(ARCHITECTURE_COMPILATION)-$(PLATEFORME_COMPILATION)
endif

# Répertoire où seront les fichiers RELEASE
ifndef REP_RELEASE
REP_RELEASE=$(REP_BUILD)/release-$(ARCHITECTURE_COMPILATION)-$(PLATEFORME_COMPILATION)
endif

# Répertoire où sont les sources
ifndef REP_SRC 
REP_SRC=
endif

# Répertoire où sont les fichiers du client
ifndef REP_SRC_CLIENT
REP_SRC_CLIENT=client
endif

# Répertoire où sont les fichiers du serveur
ifndef REP_SRC_SERVEUR 
REP_SRC_SERVEUR=serveur
endif

# Répertoire où sont les fichiers du "core"
ifndef REP_SRC_CORE 
REP_SRC_CORE=core
endif

# Définition du répertoire de compilation en fonction de si on est en debug ou non
ifndef REP_COMPILATION
	ifeq ($(DEBUG),1)
		REP_COMPILATION=$(REP_DEBUG)
	else
		REP_COMPILATION=$(REP_RELEASE)
	endif
endif

# On change les CFLAGS en fonction de la variable DEBUG
ifeq ($(DEBUG),1)
	CFLAGS="-Wall -g"
else
	CFLAGS="-Wall"
endif

# Définition des flags du linker pour le serveur
LDFLAGS_SERVEUR = 
ifeq ($(PLATEFORME_COMPILATION), mingw32)
	LDFLAGS_SERVEUR= -mconsole -lwsock32
endif

# Définition des flags du linker
LDFLAGS_CLIENT = 
ifeq ($(PLATEFORME_COMPILATION), mingw32)
	LDFLAGS_CLIENT= -mconsole -lwsock32
endif

# Commande mkdir pour créer un répertoire, elle peut varier selon les systèmes...
MKDIR=mkdir 

# Sous windows on ajoute l'extension .exe au fichier binaire
EXTENSION=
ifeq ($(PLATEFORME_COMPILATION),mingw32)
	EXTENSION=.exe
endif

# Commande de compilation serveur
define COMPILATION_SERVEUR       
	@echo "CC $<"
	$(Q)$(CC) $(CFLAGS) -std=c++11 -o $@ -c $< -DSERVEUR=1
endef

# Commande de compilation client
define COMPILATION_CLIENT       
	@echo "CC $<"
	$(Q)$(CC) $(CFLAGS) -o $@ -c $<
endef

# Exécutables
EXECUTABLES =

ifneq ($(COMPILER_CLIENT),0)
	EXECUTABLES += $(REPERTOIRE)/$(EXECUTABLE_CLIENT).$(ARCHITECTURE_COMPILATION)$(EXTENSION)
endif

ifneq ($(COMPILER_SERVEUR),0)
  	EXECUTABLES += $(REPERTOIRE)/$(EXECUTABLE_SERVEUR).$(ARCHITECTURE_COMPILATION)$(EXTENSION)
endif


# Ce qui sera exécuté lorsqu'on tapera "make"
all: 
	@$(MAKE) targets REPERTOIRE=$(REP_COMPILATION) CFLAGS=$(CFLAGS)


# Création des répertoires de compilation, affichage à la console des options
# et lancement de la compilation
targets: makedirs
	@echo ""
	@echo "Compilation du projet Bataille Spatiale."
	@echo "   VERSION: 			$(VERSION)"
	@echo "   DEBUG: 			$(DEBUG)"
	@echo "   PLATEFORME: 			$(PLATEFORME_COMPILATION)"
	@echo "   ARCHITECTURE: 		$(ARCHITECTURE_COMPILATION)"
	@echo "   COMPILATEUR: 		$(CC)"
	@echo "   CFLAGS: "
	@for i in $(CFLAGS); \
	do \
		echo "	$$i"; \
	done
	@echo ""
	@echo "   OPTIMISER: 			$(OPTIMISER)"
	@echo "   OPTIMISATIONS: 		$(OPTIMISATIONS)"
	@echo "   COMPILER CLIENT: 		$(COMPILER_CLIENT)"
	@echo "   COMPILER SERVEUR: 		$(COMPILER_SERVEUR)"
	@echo "   EXECUTABLE CLIENT: 		$(EXECUTABLE_CLIENT)"
	@echo "   EXECUTABLE SERVEUR: 		$(EXECUTABLE_SERVEUR)"
	@echo "   REPERTOIRE BUILD: 		$(REP_BUILD)"
	@echo "   REPERTOIRE DEBUG: 		$(REP_DEBUG)"
	@echo "   REPERTOIRE RELEASE: 		$(REP_RELEASE)"
	@echo "   REPERTOIRE COMPILATION: 	$(REP_COMPILATION)"
	@echo "   REPERTOIRE SOURCES: 		$(REP_SRC)"
	@echo "   REPERTOIRE SOURCES CORE: 	$(REP_SRC_CORE)"
	@echo "   REPERTOIRE SOURCES CLIENT: 	$(REP_SRC_CLIENT)"
	@echo "   REPERTOIRE SOURCES SERVEUR: 	$(REP_SRC_SERVEUR)"
	@echo ""
	@$(MAKE) $(EXECUTABLES)


# Si les répertoires de build n'existent pas, on les crée
makedirs:
	@if [ ! -d $(REP_BUILD) ]; then $(MKDIR) $(REP_BUILD); fi
	@if [ ! -d $(REP_COMPILATION) ]; then $(MKDIR) $(REP_COMPILATION); fi
	@if [ ! -d $(REPERTOIRE)/client ]; then $(MKDIR) $(REPERTOIRE)/client; fi
	@if [ ! -d $(REPERTOIRE)/serveur ]; then $(MKDIR) $(REPERTOIRE)/serveur; fi
	@if [ ! -d $(REPERTOIRE)/serveur/structures ]; then $(MKDIR) $(REPERTOIRE)/serveur/structures; fi
	@if [ ! -d $(REPERTOIRE)/serveur/structures/vaisseaux ]; then $(MKDIR) $(REPERTOIRE)/serveur/structures/vaisseaux; fi
	@if [ ! -d $(REPERTOIRE)/serveur/structures/batiments ]; then $(MKDIR) $(REPERTOIRE)/serveur/structures/batiments; fi
	@if [ ! -d $(REPERTOIRE)/serveur/structures/batiments/mines ]; then $(MKDIR) $(REPERTOIRE)/serveur/structures/batiments/mines; fi
	@if [ ! -d $(REPERTOIRE)/serveur/structures/batiments/entrepots ]; then $(MKDIR) $(REPERTOIRE)/serveur/structures/batiments/entrepots; fi
	@if [ ! -d $(REPERTOIRE)/serveur/plateau ]; then $(MKDIR) $(REPERTOIRE)/serveur/plateau; fi
	@if [ ! -d $(REPERTOIRE)/serveur/plateau/evenement ]; then $(MKDIR) $(REPERTOIRE)/serveur/plateau/evenement; fi


# Liste des fichiers .o qui seront générés

# == CLIENT ==
FICHIERS_OBJ_CLIENT = \
	$(REPERTOIRE)/client/main.o \
	$(REPERTOIRE)/client/NetworkGlobal.o \
	$(REPERTOIRE)/client/NetworkClient.o

# == SERVEUR ==
FICHIERS_OBJ_SERVEUR = \
	$(REPERTOIRE)/serveur/plateau/evenement/Evenement.o \
	$(REPERTOIRE)/serveur/plateau/Point.o \
	$(REPERTOIRE)/serveur/plateau/Noeud.o \
	$(REPERTOIRE)/serveur/plateau/Cellule.o \
	$(REPERTOIRE)/serveur/structures/Structure.o \
	$(REPERTOIRE)/serveur/structures/TechnologieStructure.o \
	$(REPERTOIRE)/serveur/structures/vaisseaux/TechnologieVaisseau.o \
	$(REPERTOIRE)/serveur/structures/vaisseaux/Vaisseau.o \
	$(REPERTOIRE)/serveur/structures/batiments/Batiment.o \
	$(REPERTOIRE)/serveur/structures/batiments/mines/Mine.o \
	$(REPERTOIRE)/serveur/structures/batiments/entrepots/Entrepot.o \
	$(REPERTOIRE)/serveur/structures/batiments/TechnologieBatiment.o \
	$(REPERTOIRE)/serveur/sv_joueur.o \
	$(REPERTOIRE)/serveur/sv_main.o \
	$(REPERTOIRE)/serveur/main.o \
	$(REPERTOIRE)/serveur/NetworkGlobal.o \
	$(REPERTOIRE)/serveur/NetworkServer.o


# Compilation du client
$(REPERTOIRE)/$(EXECUTABLE_CLIENT).$(ARCHITECTURE_COMPILATION)$(EXTENSION): $(FICHIERS_OBJ_CORE) $(FICHIERS_OBJ_CLIENT) 
	@echo ""
	@echo "$(CC) $@"
	$(Q)$(CC) -o $@ $(FICHIERS_OBJ_CLIENT) $(LDFLAGS_CLIENT)
	@echo ""

# Compilation du serveur
$(REPERTOIRE)/$(EXECUTABLE_SERVEUR).$(ARCHITECTURE_COMPILATION)$(EXTENSION): $(FICHIERS_OBJ_CORE) $(FICHIERS_OBJ_SERVEUR) 
	@echo ""
	@echo "$(CC) $@"
	$(Q)$(CC) -o $@ $(FICHIERS_OBJ_SERVEUR) $(LDFLAGS_SERVEUR)
	@echo ""


# Fichiers à compiler pour le client
#$(REPERTOIRE)/client/%.o: $(REP_SRC_CLIENT)/%.cpp
#	$(COMPILATION_CLIENT)

$(REPERTOIRE)/client/%.o: $(REP_SRC_CORE)/%.cpp
	$(COMPILATION_CLIENT)

$(REPERTOIRE)/client/%.o: %.cpp
	$(COMPILATION_CLIENT)


# Fichiers à compiler pour le serveur
$(REPERTOIRE)/serveur/%.o: $(REP_SRC_SERVEUR)/%.cpp
	$(COMPILATION_SERVEUR)

$(REPERTOIRE)/serveur/%.o: $(REP_SRC_SERVEUR)/plateau/%.cpp
	$(COMPILATION_SERVEUR)

$(REPERTOIRE)/serveur/%.o: $(REP_SRC_SERVEUR)/structures/%.cpp
	$(COMPILATION_SERVEUR)

$(REPERTOIRE)/serveur/%.o: $(REP_SRC_SERVEUR)/vaisseaux/%.cpp
	$(COMPILATION_SERVEUR)

$(REPERTOIRE)/serveur/%.o: $(REP_SRC_CORE)/%.cpp
	$(COMPILATION_SERVEUR)

$(REPERTOIRE)/serveur/%.o: %.cpp
	$(COMPILATION_SERVEUR)


.PHONY: clean 

clean:
	@rm -rf *.o
	@rm -rf $(REP_BUILD)/*

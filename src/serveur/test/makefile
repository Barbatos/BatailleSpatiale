# Le compilateur utiliser
COMPILATEUR=g++
# Les executables a créer
EXEC=testTechnologieStructure testStructure
# Le chemin des sources du serveur
CHEMIN_SRC=../
# Le chemin des sources des fonctions main
CHEMIN_SRC_MAIN=src/
# Les dossiers contenant des sources
DOSSIERS_SRC=$(CHEMIN_SRC_MAIN) $(CHEMIN_SRC) $(CHEMIN_SRC)structures/
# Le chemin ou devront être créé les executables
CHEMIN_EXE=exe/
# Options pour l'éditions des liens
LDFLAGS=
# Options pour la compilation
CFLAGS =-Wall

all: $(EXEC)

testStructure : $(CHEMIN_SRC)structures/TechnologieStructure.o $(CHEMIN_SRC)structures/Structure.o $(CHEMIN_SRC_MAIN)testStructure.o
	$(COMPILATEUR) $^ $(LDFLAGS) -o $(CHEMIN_EXE)$@

testTechnologieStructure: $(CHEMIN_SRC)structures/TechnologieStructure.o $(CHEMIN_SRC_MAIN)testTechnologieStructure.o
	$(COMPILATEUR) $^ $(LDFLAGS) -o $(CHEMIN_EXE)$@
	
%.o: %.c
	$(COMPILATEUR) $< $(CFLAGS) -c -o $@ 
	
.PHONY : clean mrproper redo

clean:
	$(foreach dossier,$(DOSSIERS_SRC),rm -rf $(dossier)*.o;)
		

mrproper: clean
	rm -rf $(CHEMIN_EXE)*
	
redo: mrproper all

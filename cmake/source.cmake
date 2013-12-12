########################################################################
#
#       Sources
#
########################################################################

# Includes
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src")

# Executable client 
SET(EXE_CLIENT "BatailleSpatiale")

# Executable serveur
SET(EXE_SERVER "ServeurBatailleSpatiale")

# Que compiler
OPTION(COMPILER_CLIENT "Compiler l'exécutable client" ON)
OPTION(COMPILER_SERVEUR "Compiler l'exécutable serveur" ON)

# Si rien n'est à compiler, erreur
IF(NOT COMPILER_CLIENT AND NOT COMPILER_SERVEUR)
    MESSAGE(FATAL_ERROR "Rien à compiler !!")
ENDIF()

# Sources du client
FILE(GLOB_RECURSE CLIENT_SRC
    "src/client/*.[ch]pp"
    "src/commun/ReseauClient.[ch]pp"
    "src/global.hpp"
)

# Sources du serveur
FILE(GLOB_RECURSE SERVEUR_SRC
    "src/serveur/*.[ch]pp"
)

# Sources communes
FILE(GLOB_RECURSE COMMUN_SRC
    "src/commun/ReseauGlobal.[ch]pp"
    "src/commun/ReseauServeur.cpp"
    "src/commun/ReseauServeur.hpp"
    "src/commun/enum/*.[ch]pp"
    "src/commun/utile/*.[ch]pp"
)

# Ajout de l'éxecutable client
IF(COMPILER_CLIENT)
    ADD_EXECUTABLE(${EXE_CLIENT} ${COMMUN_SRC} ${CLIENT_SRC})
    TARGET_LINK_LIBRARIES(${EXE_CLIENT} ${SFML_LIBRARIES})
ENDIF()

# Ajout de l'éxecutable serveur
IF(COMPILER_SERVEUR)
    ADD_EXECUTABLE(${EXE_SERVER} ${COMMUN_SRC} ${SERVEUR_SRC})
    TARGET_LINK_LIBRARIES(${EXE_SERVER} ${SFML_LIBRARIES})
ENDIF()

# Changement des flags selon les éxecutables pour windows
IF(WIN32)
    # -mwindows pour le client
    IF(COMPILER_CLIENT)
        SET_TARGET_PROPERTIES(${EXE_CLIENT} PROPERTIES COMPILE_FLAGS "-mwindows")
    ENDIF()
    
    # -mconsole pour le serveur
    IF(COMPILER_SERVEUR)
        SET_TARGET_PROPERTIES(${EXE_SERVER} PROPERTIES COMPILE_FLAGS "-mconsole")
    ENDIF()
ENDIF()

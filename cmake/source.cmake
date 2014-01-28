########################################################################
#
#       Sources
#
########################################################################

# Includes
include_directories("${SRC_DIR}")

# Executable client 
set(EXE_CLIENT "BatailleSpatiale")

# Executable serveur
set(EXE_SERVER "ServeurBatailleSpatiale")

# Exécutable Master Server
set(EXE_MASTER "MasterServeur")

# Que compiler
option(COMPILER_CLIENT "Compiler l'exécutable client" ON)
option(COMPILER_SERVEUR "Compiler l'exécutable serveur" ON)
option(COMPILER_MASTER "Compiler le Master Serveur" ON)

# Si rien n'est à compiler, erreur
if(NOT COMPILER_CLIENT AND NOT COMPILER_SERVEUR AND NOT COMPILER_MASTER)
    message(FATAL_ERROR "Rien à compiler !")
endif()

# Sources du client
file(GLOB_RECURSE CLIENT_SRC
    "${SRC_DIR}/client/*.[ch]pp"
    "${SRC_DIR}/commun/ReseauClient.[ch]pp"
    "${SRC_DIR}/global.hpp"
)

# Sources du serveur
file(GLOB_RECURSE SERVEUR_SRC
    "${SRC_DIR}/serveur/*.[ch]pp"
    "${SRC_DIR}/commun/ReseauServeur.[ch]pp"

)

# Sources du Master
file(GLOB_RECURSE MASTER_SRC
    "${SRC_DIR}/masterserveur/*.[ch]pp"
)

# Sources communes
FILE(GLOB_RECURSE COMMUN_SRC
    "src/commun/ReseauGlobal.[ch]pp"
    "src/commun/ReseauServeur.[ch]pp"
    "src/commun/enum/*.[ch]pp"
    "src/commun/utile/*.[ch]pp"
    "src/serveur/joueurs/*.[ch]pp"
    "src/serveur/plateau/*.[ch]pp"
    "src/serveur/structures/*.[ch]pp"
)

# Ajout de l'exécutable client
if(COMPILER_CLIENT)
    add_executable(${EXE_CLIENT} ${COMMUN_SRC} ${CLIENT_SRC})
    target_link_libraries(${EXE_CLIENT} ${SFML_LIBRARIES})
endif()

# Ajout de l'exécutable serveur
if(COMPILER_SERVEUR)
    add_executable(${EXE_SERVER} ${COMMUN_SRC} ${SERVEUR_SRC})
    target_link_libraries(${EXE_SERVER} ${SFML_LIBRARIES})
endif()

# Ajout de l'exécutable master server
if(COMPILER_MASTER)
    add_executable(${EXE_MASTER} ${COMMUN_SRC} ${MASTER_SRC})
    target_link_libraries(${EXE_MASTER} ${SFML_LIBRARIES})
endif()

# Changement des flags selon les éxecutables pour windows
if(WIN32)
    # -mwindows pour le client
    if(COMPILER_CLIENT)
        set_target_properties(${EXE_CLIENT} PROPERTIES COMPILE_FLAGS "-mwindows")
    endif()
    
    # -mconsole pour le serveur
    if(COMPILER_SERVEUR)
        set_target_properties(${EXE_SERVER} PROPERTIES COMPILE_FLAGS "-mconsole")
    endif()

    # -mconsole pour le master
    if(COMPILER_MASTER)
        set_target_properties(${EXE_MASTER} PROPERTIES COMPILE_FLAGS "-mconsole")
    endif()
endif()

cmake_minimum_required(VERSION 2.6)

project(BatailleSpatiale)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_BUILD_PATH ${CMAKE_SOURCE_DIR}/build)
set(EXE_OUTPUT_PATH ${CMAKE_BUILD_PATH}/${CMAKE_BUILD_TYPE})

set(EXE_CLIENT "BatailleSpatiale")
set(EXE_SERVER "ServeurBatailleSpatiale")

set(CMAKE_CXX_FLAGS "-std=c++11 -std=gnu++11 -Wall")
if(WIN32)
	# Le répertoire où est installée la sfml (windows uniquement)
	set(SFML_DIR "C:/SFML/")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows -mconsole -lwsock32")
endif()

option(COMPILER_CLIENT "Compiler l'exécutable client" ON)
option(COMPILER_SERVEUR "Compiler l'exécutable serveur" ON)

if(NOT COMPILER_CLIENT AND NOT COMPILER_SERVEUR)
	message(FATAL_ERROR "Rien à compiler !!")
endif()

file(GLOB COMMUN_SRC
	"src/global.hpp"
	"src/commun/ReseauGlobal.cpp"
	"src/commun/ReseauGlobal.hpp"
)
source_group("commun" FILES  ${COMMUN_SRC})

file(GLOB_RECURSE CLIENT_SRC
    "src/client/*.[ch]pp"
)
source_group("client" FILES  ${CLIENT_SRC})

file(GLOB_RECURSE SERVEUR_SRC
    "src/serveur/*.[ch]pp"
    "src/commun/ReseauServeur.cpp"
    "src/commun/ReseauServeur.hpp"
)
source_group("serveur" FILES  ${SERVEUR_SRC})

find_package(SFML 2 REQUIRED network system)

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIRS})

if(COMPILER_CLIENT)
	add_executable(${EXE_CLIENT} ${COMMUN_SRC} ${CLIENT_SRC})
	target_link_libraries(${EXE_CLIENT} ${SFML_LIBRARIES})
endif()

if(COMPILER_SERVEUR)
	add_executable(${EXE_SERVER} ${COMMUN_SRC} ${SERVEUR_SRC})
	target_link_libraries(${EXE_SERVER} ${SFML_LIBRARIES})
endif()

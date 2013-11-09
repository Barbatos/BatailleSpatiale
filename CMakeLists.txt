cmake_minimum_required(VERSION 2.6)

project(BatailleSpatiale)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_BUILD_PATH ${CMAKE_SOURCE_DIR}/build)
set(EXE_OUTPUT_PATH ${CMAKE_BUILD_PATH}/${CMAKE_BUILD_TYPE})

set(EXE_CLIENT "BatailleSpatiale")
set(EXE_SERVER "Serveur")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
if(WIN32)
	# Le répertoire où est installée la sfml (windows uniquement)
	set(SFML_DIR "C:/SFML/")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mconsole -lwsock32")
endif()

option(BUILD_CLIENT "Build the client executable" ON)
option(BUILD_SERVER "Build the dedicated server executable" ON)

if(NOT BUILD_CLIENT AND NOT BUILD_SERVER)
	message(FATAL_ERROR "Rien à compiler !!")
endif()

file(GLOB CORE_SRC
	"src/main.cpp"
	"src/global.hpp"
	"src/core/ReseauGlobal.cpp"
	"src/core/ReseauGlobal.hpp"
)
source_group("core" FILES  ${CORE_SRC})

file(GLOB_RECURSE CLIENT_SRC
    "src/client/*.[ch]pp"
)
source_group("client" FILES  ${CLIENT_SRC})

file(GLOB_RECURSE SERVER_SRC
    "src/serveur/*.[ch]pp"
    "src/core/ReseauServeur.cpp"
    "src/core/ReseauServeur.hpp"
)
source_group("server" FILES  ${SERVER_SRC})

find_package(SFML 2 REQUIRED network system)

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIRS})

if(BUILD_CLIENT)
	add_executable(${EXE_CLIENT} ${CORE_SRC} ${CLIENT_SRC})
	target_link_libraries(${EXE_CLIENT} ${SFML_LIBRARIES})
endif()

if(BUILD_SERVER)
	add_executable(${EXE_SERVER} ${CORE_SRC} ${SERVER_SRC})
	target_link_libraries(${EXE_SERVER} ${SFML_LIBRARIES})
endif()

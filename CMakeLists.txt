########################################################################
#
#       General
#
########################################################################

# Version de cmake minimum
cmake_minimum_required(VERSION 2.6)

# Projet bataille spatiale
project(BatailleSpatiale)

# Build type par défaut à Debug
if(CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
ENDIF()

# Change le dossier des modules cmake
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

# Dossier de build
set(CMAKE_BUILD_PATH ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

# Change le dossier où seront créés les éxecutables
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Change les flags de compilation
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra")

########################################################################
#
#       Librairies
#
########################################################################

# On inclut le chargement de la SFML
INCLUDE(cmake/sfml.cmake)

########################################################################
#
#       Sources
#
########################################################################

# On inclut les sources
INCLUDE(cmake/source.cmake)

########################################################################
#
#       Ressources
#
########################################################################

# On inclut la copie des ressources
INCLUDE(cmake/ressources.cmake)

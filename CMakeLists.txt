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
endif()

# Localisation de différents dossiers
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

# Changement de quelques dossiers utilisés par CMake
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
set(CMAKE_BUILD_PATH "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")

# Change les flags de compilation
set(CMAKE_CXX_FLAGS "-std=c++0x -Wall -Wextra -Werror -pedantic")

########################################################################
#
#       Librairies
#
########################################################################

# On inclut le chargement de la SFML
include("cmake/sfml.cmake")

########################################################################
#
#       Sources
#
########################################################################

# On inclut les sources
include("cmake/source.cmake")

########################################################################
#
#       Ressources
#
########################################################################

# On inclut la copie des ressources
include("cmake/ressources.cmake")

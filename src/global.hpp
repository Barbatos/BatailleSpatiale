#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif
#include <stdio.h>
#include <map>
#include <list>
#include <memory>

#ifdef WIN32
#pragma comment(lib, "sfml-network.lib")
#endif

// You need SFML >= 2.0
// http://en.sfml-dev.org/forums/index.php?topic=11338.0
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

using namespace std;

// Version du jeu
#define VERSION 	0.1.1

// Mode débug
#define DEBUG 		1


#endif

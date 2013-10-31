#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <map>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/iter_find.hpp>
#include <boost/lexical_cast.hpp>

#pragma comment(lib, "sfml-network.lib")

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

using namespace std;

#include "core/NetworkGlobal.hpp"

#ifdef SERVEUR
	#include "core/NetworkServer.hpp"
	//#include "serveur/sv_joueur.hpp"
#else
	#include "core/NetworkClient.hpp"
#endif

// Version du jeu
#define VERSION 	0.1.1

// Mode débug
#define DEBUG 		1


void SV_Frame();

#endif 

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/iter_find.hpp>

#include "core/network.hpp"

#ifdef SERVEUR
#include "serveur/sv_joueur.hpp"
#endif

using namespace std;

// Version du jeu
#define VERSION 	0.1.1

// Mode débug
#define DEBUG 		1


void SV_Frame();

#endif 

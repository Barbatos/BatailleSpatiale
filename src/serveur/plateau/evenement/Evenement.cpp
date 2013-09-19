#include <iostream>
#include "Evenement.hpp"

Evenement::Evenement(int _coutDeplacement){
	coutDeplacement = _coutDeplacement;
}

bool Evenement::accessible(){
	return coutDeplacement != -1;
}
	
int Evenement::getCoutDeplacement(){
	return coutDeplacement;
}

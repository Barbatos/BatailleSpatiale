#include "Mine.hpp"

Mine::Mine() : Batiment(){
    production = 0;

}

/*Mine::Mine(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int niveau, int production) :
    Structure(vieMax, bouclierMax, bouclierTaux, visibilite, attaque, niveau){

    this->production = production;

}*/

int Mine::getProduction(){
    return production;

}


void Mine::setProduction(int production){
    this->production = production;

}


void Mine::ajouterEntrepot(Entrepot entrepot){
    listeEntrepot.push_back(entrepot);


}

void Mine::retirerEntrepot(){
    if(!listeEntrepot.empty())
        listeEntrepot.pop_back();

}

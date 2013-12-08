#include "Constructeur.hpp"

Constructeur::Constructeur() : Vaisseau(){
	materiaux = this->materiauxMax;
}

Constructeur::Constructeur(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int energieMax, int consommationMax, int _materiauxMax ) :
    Vaisseau(vieMax, bouclierMax, bouclierTaux, visibilite, attaque, energieMax, consommationMax), materiaux(_materiauxMax), materiauxMax(_materiauxMax) {

}



int Constructeur::getMateriaux(){
    return materiaux;

}

void Constructeur::setMateriaux(int materiaux){
    this->materiaux = materiaux;

}

int Constructeur::getMateriauxMax(){
    return materiauxMax;

}

void Constructeur::setMateriauxMax(int materiauxMax){
    this->materiauxMax = materiauxMax;

}

void Constructeur::ajouterBatiment(Batiment batiment){
    listeConstruction.push_back(batiment);


}

void Constructeur::retirerBatiment(){
    if(!listeConstruction.empty())
        listeConstruction.pop_back();

}










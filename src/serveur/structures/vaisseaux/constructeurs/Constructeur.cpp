#include "Constructeur.hpp"


Constructeur::Constructeur() : VaisseauServeur(){

    ajouterBatiment(BatimentServeur(1500, 300, 0.4f, 120, 0, 1, 0, 1000, 1000, TypeBatiment::Bidon));
    ajouterBatiment(BatimentServeur(1100, 100, 0.4f, 250, 350, 1, 100, 1500, 1000, TypeBatiment::Bidon));
    ajouterBatiment(BatimentServeur(900, 700, 0.8f, 100, 0, 1, 0, 700, 1000, TypeBatiment::Bidon));
}

Constructeur::Constructeur(sf::Int32 vieMax, sf::Int32 bouclierMax, float bouclierTaux, sf::Int32 visibilite, sf::Int32 attaque, sf::Int32 energieMax, sf::Int32 consommationMax, sf::Int32 rayonAttaque, sf::Int32 prixEnergie, sf::Int32 prixMateriaux) :
    VaisseauServeur(vieMax, bouclierMax, bouclierTaux, visibilite, attaque, energieMax, consommationMax, rayonAttaque, prixEnergie, prixMateriaux, TypeVaisseau::Constructeur) {

    ajouterBatiment(BatimentServeur(1500, 300, 0.4f, 120, 0, 1, 0, 1000, 1000, TypeBatiment::Bidon));
    ajouterBatiment(BatimentServeur(1100, 100, 0.4f, 250, 350, 1, 100, 1500, 1000, TypeBatiment::Bidon));
    ajouterBatiment(BatimentServeur(900, 700, 0.8f, 100, 0, 1, 0, 700, 1000, TypeBatiment::Bidon));

}

BatimentServeur Constructeur::getBatiment(int index){
        return listeConstruction.at(index);
}

void Constructeur::ajouterBatiment(BatimentServeur batiment){
    listeConstruction.push_back(batiment);


}

void Constructeur::retirerBatiment(){
    if(!listeConstruction.empty())
        listeConstruction.pop_back();

}













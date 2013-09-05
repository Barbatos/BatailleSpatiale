#include "Vaisseau.hpp"

Vaisseau::Vaisseau() : Structure() {

    energie = 0;
    energieMax = 0;
    consommationMax = 0;

}

Vaisseau::Vaisseau(int vieMax, int bouclierMax, float bouclierTaux, int visibilite, int attaque, int energieMax, int consommationMax):
    Structure(vieMax, bouclierMax, bouclierTaux, visibilite, attaque){

    energie = this->energieMax = energieMax;
    this->consommationMax = consommationMax;

}

// Getters
int Vaisseau::getEnergie() const{
    return energie;
}

int Vaisseau::getEnergieMax() const{
    return energieMax;
}

int Vaisseau::getConsommationMax() const{
    return consommationMax;
}


// Setters
void Vaisseau::setEnergie(int const energie){

    if(energie < 0) this->energie = 0;
    else if(energie <= energieMax) this->energie = energie;
    else this->energie = energieMax;

}


void Vaisseau::setEnergieMax(int const energieMax){

    this->energieMax = energieMax;

}

void Vaisseau::setConsommationMax(int const consommationMax){

    this->consommationMax = consommationMax;

}

void Vaisseau::modifierEnergie(int const valeur){

    if(energie + valeur < energieMax){
        this->setVie(energie + valeur);
        if(valeur > 0) cout << valeur << " points d' energie ont ete rendus au vaisseau" << endl << endl;
        if(valeur < 0) cout << "Le vaisseau a perdu " << -valeur << " points d'energie" << endl << endl;
    }
    else this->setVie(energieMax);

}


void Vaisseau::afficher(ostream& fluxSortant) const {

    fluxSortant << "Vie : " << vie << "/" << vieMax << endl <<
				   "Bouclier : " << bouclier << "/" << bouclierMax << endl <<
				   "% degats absorbes : " << (bouclierTaux*100) << "%" << endl <<
				   "Visibilite : " << visibilite << endl <<
				   "Attaque : " << attaque << endl <<
				   "Energie : " << energie << "/" << energieMax << endl <<
				   "Consommation : " << consommationMax << endl << endl;


}

ostream& operator<<(ostream& fluxSortant, Vaisseau const& Vaisseau) {

    Vaisseau.afficher(fluxSortant) ;
    return fluxSortant;

}



Vaisseau Vaisseau::cloner(Vaisseau const& modele, TechnologieStructure techS, TechnologieVaisseau techV){

    Structure base = Structure::cloner(modele, techS);

    return Vaisseau(base.getVieMax(),
                    base.getBouclierMax(),
                    base.getBouclierTaux(),
                    base.getVisibilite(),
                    base.getAttaque(),
                    modele.getEnergieMax() + (modele.getEnergieMax() * 0.5 * techV.getNiveauEnergie()),
                    modele.getConsommationMax() - (modele.getConsommationMax() * 0.1 * techV.getNiveauConsommation()));

}






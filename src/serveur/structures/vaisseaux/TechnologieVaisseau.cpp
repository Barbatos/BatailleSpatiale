#include "TechnologieVaisseau.hpp"

/*
 * Cette classe ne contient que les niveaux influençant touts les vaisseaux
 * Le constructeur met tous les niveaux à 0
 */
TechnologieVaisseau::TechnologieVaisseau():
	niveauDistance(0), niveauConsommation(0){

}

unsigned int TechnologieVaisseau::getNiveauDistance() const {
	return niveauDistance;
}

unsigned int TechnologieVaisseau::getNiveauConsommation() const {
	return niveauConsommation;
}


bool TechnologieVaisseau::augmenterNiveauDistance(unsigned int const& gainNiveau){
	// Le niveau Energie ne peut pas augmenter de plus de 5 niveaux à la fois
	if(gainNiveau > 5)
		return false;

	// Si il n'est pas supérieur à 5 on l'augmente de [gainNiveau]
	niveauDistance += gainNiveau;
	return true;
}

bool TechnologieVaisseau::augmenterNiveauConsommation(unsigned int const& gainNiveau){
	// Le niveau Consommation ne peut pas augmenter de plus de 3 niveaux en même temps
	if(gainNiveau > 3)
		return false;

	// Si il n'est pas supérieur à 3 on l'augmente de [gainNiveau]
	niveauConsommation += gainNiveau;
	return true;
}


void TechnologieVaisseau::changerFlux(std::ostream& fluxSortant) const {
	// On retourne dans [fluxSortant] les attributs
    fluxSortant << "Niveau Distance : " << niveauDistance << std::endl <<
				   "Niveau Consommation : " << niveauConsommation << std::endl;
}

std::ostream& operator<<(std::ostream& fluxSortant, TechnologieVaisseau const& technologieVaisseau) {
	// On modifie [fluxSortant]
    technologieVaisseau.changerFlux(fluxSortant) ;
    // Et on le retourne
    return fluxSortant;
}


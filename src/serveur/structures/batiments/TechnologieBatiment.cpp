#include "TechnologieBatiment.hpp"

/*
 * Cette classe ne contient que les niveaux influençant touts les vaisseaux
 * Le constructeur met tous les niveaux à 0
 */
TechnologieBatiment::TechnologieBatiment():
	niveauAchat(0), niveauCoutEnergie(0), niveauCoutMateriaux(0){

}

unsigned int TechnologieBatiment::getNiveauAchat() const {
	return niveauAchat;
}

unsigned int TechnologieBatiment::getNiveauCoutEnergie() const {
	return niveauCoutEnergie;
}

unsigned int TechnologieBatiment::getNiveauCoutMateriaux() const {
	return niveauCoutMateriaux;
}


bool TechnologieBatiment::augmenterNiveauAchat(unsigned int const& gainNiveau){
	// Le niveau Materiaux ne peut pas augmenter de plus de 10 niveaux à la fois
	if(gainNiveau > 10)
		return false;

	// Si il n'est pas supérieur à 10 on l'augmente de [gainNiveau]
	niveauAchat += gainNiveau;
	return true;
}

bool TechnologieBatiment::augmenterNiveauCoutEnergie(unsigned int const& gainNiveau){
	// Le niveau Energie ne peut pas augmenter de plus de 5 niveaux à la fois
	if(gainNiveau > 5)
		return false;

	// Si il n'est pas supérieur à 5 on l'augmente de [gainNiveau]
	niveauCoutEnergie += gainNiveau;
	return true;
}

bool TechnologieBatiment::augmenterNiveauCoutMateriaux(unsigned int const& gainNiveau){
	// Le niveau Consommation ne peut pas augmenter de plus de 3 niveaux en même temps
	if(gainNiveau > 3)
		return false;

	// Si il n'est pas supérieur à 3 on l'augmente de [gainNiveau]
	niveauCoutMateriaux += gainNiveau;
	return true;
}


void TechnologieBatiment::changerFlux(std::ostream& fluxSortant) const {
	// On retourne dans [fluxSortant] les attributs
    fluxSortant << "Niveau Achat : " << niveauAchat << std::endl <<
				   "Niveau Cout Energie : " << niveauCoutEnergie << std::endl <<
				   "Niveau Cout Materiaux : " << niveauCoutMateriaux << std::endl;
}

std::ostream& operator<<(std::ostream& fluxSortant, TechnologieBatiment const& technologieBatiment) {
	// On modifie [fluxSortant]
    technologieBatiment.changerFlux(fluxSortant) ;
    // Et on le retourne
    return fluxSortant;
}

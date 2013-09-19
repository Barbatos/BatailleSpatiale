
#include "TechnologieVaisseau.hpp"

/*
 * Cette classe ne contient que les niveaux influen�ant touts les vaisseaux
 * Le constructeur met tous les niveaux � 0
 */
TechnologieVaisseau::TechnologieVaisseau():
	niveauMateriaux(0), niveauEnergie(0), niveauConsommation(0){

}

unsigned int TechnologieVaisseau::getNiveauMateriaux() const {
	return niveauMateriaux;
}

unsigned int TechnologieVaisseau::getNiveauEnergie() const {
	return niveauEnergie;
}

unsigned int TechnologieVaisseau::getNiveauConsommation() const {
	return niveauConsommation;
}


bool TechnologieVaisseau::augmenterNiveauMateriaux(unsigned int const& gainNiveau){
	// Le niveau Materiaux ne peut pas augmenter de plus de 10 niveaux � la fois
	if(gainNiveau > 10)
		return false;

	// Si il n'est pas sup�rieur � 10 on l'augmente de [gainNiveau]
	niveauMateriaux += gainNiveau;
	return true;
}

bool TechnologieVaisseau::augmenterNiveauEnergie(unsigned int const& gainNiveau){
	// Le niveau Energie ne peut pas augmenter de plus de 5 niveaux � la fois
	if(gainNiveau > 5)
		return false;

	// Si il n'est pas sup�rieur � 5 on l'augmente de [gainNiveau]
	niveauEnergie += gainNiveau;
	return true;
}

bool TechnologieVaisseau::augmenterNiveauConsommation(unsigned int const& gainNiveau){
	// Le niveau Consommation ne peut pas augmenter de plus de 3 niveaux en m�me temps
	if(gainNiveau > 3)
		return false;

	// Si il n'est pas sup�rieur � 3 on l'augmente de [gainNiveau]
	niveauConsommation += gainNiveau;
	return true;
}


void TechnologieVaisseau::changerFlux(std::ostream& fluxSortant) const {
	// On retourne dans [fluxSortant] les attributs
    fluxSortant << "Niveau Materiaux : " << niveauMateriaux << std::endl <<
				   "Niveau Energie : " << niveauEnergie << std::endl <<
				   "Niveau Consommation : " << niveauConsommation << std::endl;
}

std::ostream& operator<<(std::ostream& fluxSortant, TechnologieVaisseau const& technologieVaisseau) {
	// On modifie [fluxSortant]
    technologieVaisseau.changerFlux(fluxSortant) ;
    // Et on le retourne
    return fluxSortant;
}


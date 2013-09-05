#include "TechnologieStructure.hpp"

/*
 * Cette classe ne contient que les niveaux influençant toutes les structures
 * Le constructeur met tous les niveaux à 0
 */
TechnologieStructure::TechnologieStructure():
	niveauAttaque(0), niveauBouclier(0), niveauVie(0), niveauVisibilite(0){
	  
}

unsigned int TechnologieStructure::getNiveauAttaque() const {
	return niveauAttaque;
}

unsigned int TechnologieStructure::getNiveauBouclier() const {
	return niveauBouclier;
}

unsigned int TechnologieStructure::getNiveauVie() const {
	return niveauVie;
}

unsigned int TechnologieStructure::getNiveauVisibilite() const {
	return niveauVisibilite;
}

bool TechnologieStructure::augmenterNiveauAttaque(unsigned int const& gainNiveau){
	// Le niveau Attaque ne peut pas augmenter de plus de 10 niveaux à la fois 
	if(gainNiveau > 10) 
		return false;
	
	// Si il n'est pas supérieur à 10 on l'augmente de [gainNiveau]
	niveauAttaque += gainNiveau;
	return true;
}

bool TechnologieStructure::augmenterNiveauBouclier(unsigned int const& gainNiveau){
	// Le niveau Bouclier ne peut pas augmenter de plus de 5 niveaux à la fois 
	if(gainNiveau > 5) 
		return false;
	
	// Si il n'est pas supérieur à 5 on l'augmente de [gainNiveau]
	niveauBouclier += gainNiveau;
	return true;
}

bool TechnologieStructure::augmenterNiveauVie(unsigned int const& gainNiveau){
	// Le niveau Vie ne peut pas augmenter de plus de 3 niveaux en même temps 
	if(gainNiveau > 3) 
		return false;
	
	// Si il n'est pas supérieur à 3 on l'augmente de [gainNiveau]
	niveauVie += gainNiveau;
	return true;
}

bool TechnologieStructure::augmenterNiveauVisibilite(unsigned int const& gainNiveau){
	// Le niveau Visibilité ne peut pas augmenter de plus de 2 niveaux à la fois 
	if(gainNiveau > 2) 
		return false;
	
	// Si il n'est pas supérieur à 2 on l'augmente de [gainNiveau]
	niveauVisibilite += gainNiveau;
	return true;
}

void TechnologieStructure::changerFlux(std::ostream& fluxSortant) const {
	// On retourne dans [fluxSortant] les attributs
    fluxSortant << "Niveau Attaque : " << niveauAttaque << std::endl <<
				   "Niveau Bouclier : " << niveauBouclier << std::endl <<
				   "Niveau Vie : " << niveauVie << std::endl <<
				   "Niveau Visibilité : " << niveauVisibilite << std::endl;
}

std::ostream& operator<<(std::ostream& fluxSortant, TechnologieStructure const& technologieStructure) {
	// On modifie [fluxSortant]
    technologieStructure.changerFlux(fluxSortant) ;
    // Et on le retourne
    return fluxSortant;
}

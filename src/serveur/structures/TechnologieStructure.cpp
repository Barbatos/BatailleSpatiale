#include "TechnologieStructure.hpp"

/*
 * Cette classe ne contient que les niveaux influen�ant toutes les structures
 * Le constructeur met tous les niveaux � 0
 */
TechnologieStructure::TechnologieStructure():
	niveauAttaque(0), niveauBouclier(0), niveauVie(0), niveauVisibilite(0), niveauMateriaux(0){

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

unsigned int TechnologieStructure::getNiveauMateriaux() const {
	return niveauMateriaux;
}

bool TechnologieStructure::augmenterNiveauAttaque(unsigned int const& gainNiveau){
	// Le niveau Attaque ne peut pas augmenter de plus de 10 niveaux � la fois
	if(gainNiveau > 10)
		return false;

	// Si il n'est pas sup�rieur � 10 on l'augmente de [gainNiveau]
	niveauAttaque += gainNiveau;
	return true;
}

bool TechnologieStructure::augmenterNiveauBouclier(unsigned int const& gainNiveau){
	// Le niveau Bouclier ne peut pas augmenter de plus de 5 niveaux � la fois
	if(gainNiveau > 5)
		return false;

	// Si il n'est pas sup�rieur � 5 on l'augmente de [gainNiveau]
	niveauBouclier += gainNiveau;
	return true;
}

bool TechnologieStructure::augmenterNiveauVie(unsigned int const& gainNiveau){
	// Le niveau Vie ne peut pas augmenter de plus de 3 niveaux en m�me temps
	if(gainNiveau > 3)
		return false;

	// Si il n'est pas sup�rieur � 3 on l'augmente de [gainNiveau]
	niveauVie += gainNiveau;
	return true;
}

bool TechnologieStructure::augmenterNiveauVisibilite(unsigned int const& gainNiveau){
	// Le niveau Visibilit� ne peut pas augmenter de plus de 2 niveaux � la fois
	if(gainNiveau > 2)
		return false;

	// Si il n'est pas sup�rieur � 2 on l'augmente de [gainNiveau]
	niveauVisibilite += gainNiveau;
	return true;
}

bool TechnologieStructure::augmenterNiveauMateriaux(unsigned int const& gainNiveau){
	// Le niveau Visibilit� ne peut pas augmenter de plus de 2 niveaux � la fois
	if(gainNiveau > 2)
		return false;

	// Si il n'est pas sup�rieur � 2 on l'augmente de [gainNiveau]
	niveauMateriaux += gainNiveau;
	return true;
}

void TechnologieStructure::changerFlux(std::ostream& fluxSortant) const {
	// On retourne dans [fluxSortant] les attributs
    fluxSortant << "Niveau Attaque : " << niveauAttaque << std::endl <<
				   "Niveau Bouclier : " << niveauBouclier << std::endl <<
				   "Niveau Vie : " << niveauVie << std::endl <<
				   "Niveau Visibilite : " << niveauVisibilite << std::endl <<
				   "Niveau Materiaux : " << niveauMateriaux << std::endl;
}

std::ostream& operator<<(std::ostream& fluxSortant, TechnologieStructure const& technologieStructure) {
	// On modifie [fluxSortant]
    technologieStructure.changerFlux(fluxSortant) ;
    // Et on le retourne
    return fluxSortant;
}


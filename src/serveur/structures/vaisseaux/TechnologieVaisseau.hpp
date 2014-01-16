#ifndef TECHNOLOGIE_VAISSEAU_HPP
#define TECHNOLOGIE_VAISSEAU_HPP
#include <iostream>

/*
 * Classe qui définit les technologies sur les vaisseaux
 * que possède le joueur.
 * Elle est utile lorsque l'on crée un nouveau vaisseau
 */

class TechnologieVaisseau {

public:

	TechnologieVaisseau();
	// Getters
	unsigned int getNiveauMateriaux() const;
	unsigned int getNiveauDistance() const;
	unsigned int getNiveauConsommation() const;
	// Des méthodes pour augmenter les niveaux
	bool augmenterNiveauMateriaux(unsigned int const& gainNiveau);
	bool augmenterNiveauDistance(unsigned int const& gainNiveau);
	bool augmenterNiveauConsommation(unsigned int const& gainNiveau);


private:

	// Cette classe possède différents niveaux utiles pour toutes les structures
	unsigned int niveauMateriaux;
	unsigned int niveauDistance;
	unsigned int niveauConsommation;

	// Deux méthodes pour afficher notre structure
	void changerFlux(std::ostream &fluxSortant) const;
	friend std::ostream& operator<< (std::ostream& fluxSortant, TechnologieVaisseau const& technologieVaisseau);
};


#endif // TECHNOLOGIE_VAISSEAU_HPP

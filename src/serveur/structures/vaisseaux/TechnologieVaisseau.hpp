#ifndef TECHNOLOGIE_VAISSEAU_HPP
#define TECHNOLOGIE_VAISSEAU_HPP
#include <iostream>

/*
 * Classe qui d�finit les technologies sur les vaisseaux
 * que poss�de le joueur.
 * Elle est utile lorsque l'on cr�e un nouveau vaisseau
 */

class TechnologieVaisseau {

	public:

		TechnologieVaisseau();
		// Getters
		unsigned int getNiveauDistance() const;
		unsigned int getNiveauConsommation() const;
		// Des m�thodes pour augmenter les niveaux
		bool augmenterNiveauDistance(unsigned int const& gainNiveau);
		bool augmenterNiveauConsommation(unsigned int const& gainNiveau);


	private:

		// Cette classe poss�de diff�rents niveaux utiles pour toutes les structures
		unsigned int niveauDistance;
		unsigned int niveauConsommation;

		// Deux m�thodes pour afficher notre structure
		void changerFlux(std::ostream &fluxSortant) const;
		friend std::ostream& operator<< (std::ostream& fluxSortant, TechnologieVaisseau const& technologieVaisseau);
};


#endif // TECHNOLOGIE_VAISSEAU_HPP




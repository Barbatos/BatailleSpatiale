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
		unsigned int getNiveauMateriaux() const;
		unsigned int getNiveauEnergie() const;
		unsigned int getNiveauConsommation() const;
		// Des m�thodes pour augmenter les niveaux
		bool augmenterNiveauMateriaux(unsigned int const& gainNiveau);
		bool augmenterNiveauEnergie(unsigned int const& gainNiveau);
		bool augmenterNiveauConsommation(unsigned int const& gainNiveau);


	private:

		// Cette classe poss�de diff�rents niveaux utiles pour toutes les structures
		unsigned int niveauMateriaux;
		unsigned int niveauEnergie;
		unsigned int niveauConsommation;

		// Deux m�thodes pour afficher notre structure
		void changerFlux(std::ostream &fluxSortant) const;
		friend std::ostream& operator<< (std::ostream& fluxSortant, TechnologieVaisseau const& technologieVaisseau);
};


#endif // TECHNOLOGIE_VAISSEAU_HPP



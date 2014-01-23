
#ifndef TECHNOLOGIE_BATIMENT_HPP
#define TECHNOLOGIE_BATIMENT_HPP
#include <iostream>

/*
 * Classe qui d�finit les technologies sur les vaisseaux
 * que poss�de le joueur.
 * Elle est utile lorsque l'on cr�e un nouveau vaisseau
 */

class TechnologieBatiment {

	public:

		TechnologieBatiment();
		// Getters
		unsigned int getNiveauAchat() const;
		unsigned int getNiveauCoutEnergie() const;
		unsigned int getNiveauCoutMateriaux() const;
		// Des m�thodes pour augmenter les niveaux
		bool augmenterNiveauAchat(unsigned int const& gainNiveau);
		bool augmenterNiveauCoutEnergie(unsigned int const& gainNiveau);
		bool augmenterNiveauCoutMateriaux(unsigned int const& gainNiveau);


	private:

		// Cette classe poss�de diff�rents niveaux utiles pour toutes les structures
		unsigned int niveauAchat;
		unsigned int niveauCoutEnergie;
		unsigned int niveauCoutMateriaux;

		// Deux m�thodes pour afficher notre structure
		void changerFlux(std::ostream &fluxSortant) const;
		friend std::ostream& operator<< (std::ostream& fluxSortant, TechnologieBatiment const& technologieBatiment);
};


#endif // TECHNOLOGIE_BATIMENT_HPP




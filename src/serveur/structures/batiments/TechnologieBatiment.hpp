
#ifndef TECHNOLOGIE_BATIMENT_HPP
#define TECHNOLOGIE_BATIMENT_HPP
#include <iostream>

/*
 * Classe qui définit les technologies sur les vaisseaux
 * que possède le joueur.
 * Elle est utile lorsque l'on crée un nouveau vaisseau
 */

class TechnologieBatiment {

	public:

		TechnologieBatiment();
		// Getters
		unsigned int getNiveauAchat() const;
		unsigned int getNiveauCoutEnergie() const;
		unsigned int getNiveauCoutMateriaux() const;
		// Des méthodes pour augmenter les niveaux
		bool augmenterNiveauAchat(unsigned int const& gainNiveau);
		bool augmenterNiveauCoutEnergie(unsigned int const& gainNiveau);
		bool augmenterNiveauCoutMateriaux(unsigned int const& gainNiveau);


	private:

		// Cette classe possède différents niveaux utiles pour toutes les structures
		unsigned int niveauAchat;
		unsigned int niveauCoutEnergie;
		unsigned int niveauCoutMateriaux;

		// Deux méthodes pour afficher notre structure
		void changerFlux(std::ostream &fluxSortant) const;
		friend std::ostream& operator<< (std::ostream& fluxSortant, TechnologieBatiment const& technologieBatiment);
};


#endif // TECHNOLOGIE_BATIMENT_HPP




#ifndef TECHNOLOGIE_STRUCTURE_HPP
#define TECHNOLOGIE_STRUCTURE_HPP

#include <iostream>

/*
 * Classe qui d�finit les technologies sur les structures
 * que poss�de le joueur.
 * Elle est utile lorsque l'on cr�e une nouvelle structure
 */

class TechnologieStructure {

	public:

		TechnologieStructure();

		// Getters
		unsigned int getNiveauAttaque() const;
		unsigned int getNiveauBouclier() const;
		unsigned int getNiveauVie() const;
		unsigned int getNiveauVisibilite() const;
		unsigned int getNiveauMateriaux() const;

		// Des m�thodes pour augmenter les niveaux
		bool augmenterNiveauAttaque(unsigned int const& gainNiveau);
		bool augmenterNiveauBouclier(unsigned int const& gainNiveau);
		bool augmenterNiveauVie(unsigned int const& gainNiveau);
		bool augmenterNiveauVisibilite(unsigned int const& gainNiveau);
		bool augmenterNiveauMateriaux(unsigned int const& gainNiveau);


	private:

		// Cette classe poss�de diff�rents niveaux utiles pour toutes les structures
		unsigned int niveauAttaque;
		unsigned int niveauBouclier;
		unsigned int niveauVie;
		unsigned int niveauVisibilite;
		unsigned int niveauMateriaux;

		// Deux m�thodes pour afficher notre structure
		void changerFlux(std::ostream &fluxSortant) const;
		friend std::ostream& operator<<(std::ostream& fluxSortant, TechnologieStructure const& technologieStructure);
};

#endif // TECHNOLOGIE_STRUCTURE_HPP


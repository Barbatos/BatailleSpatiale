#ifndef EVENEMENT_HPP
#define EVENEMENT_HPP
#include <iostream>
#include <memory>
#include "../../structures/batiments/Batiment.hpp"
#include "../../structures/vaisseaux/Vaisseau.hpp"

/*
 * Classe qui permet d'affecter les vaisseaux
 * selon certains paramêtres
 */

class Evenement {
	
	public:
		//Constructeurs
		Evenement();
		Evenement(
			char* name, 
			bool destructible, 
			int _coutDeplacement, 
			int _multiplicateurDommage, 
			int _multiplicateurDegat
		);
		
		//Setters
		virtual void activer(Batiment* batiment) {}
		virtual void desactiver(Batiment* batiment) {}
		virtual void activer(Vaisseau* vaisseau) {}
		virtual void desactiver(Vaisseau* vaisseau) {}
		
		//Getters
		char* quelNom();
		bool estDestructible();
		bool estAccessible();
		bool tirPossible();
		bool ciblePossible();
		int getCoutDeplacement();
		int getMultiplicateurDommage();
		int getMultiplicateurDegat();
		
	private:
		// Nom de l'évènements.
		char* name;
		// l'évenement est destructible, on remonte une structure qui prend sa place.
		bool destructible;
		// nombre de deplacement a utiliser pour passer par cette case 1 par défaut -1 pour impossible
		int coutDeplacement;
		// paramètre à prendre en compte lors du calcul des dommages infligés par la structure présente.
		int multiplicateurDommage;
		// paramètre à prendre en compte lors du calcul des dommages subits par la structure présente.
		int multiplicateurDegat;
};

typedef std::shared_ptr<Evenement> EvenementPtr;

#endif // EVENEMENT_HPP
#ifndef EVENEMENT_HPP
#define EVENEMENT_HPP
#include <iostream>
#include <memory>
<<<<<<< HEAD
#include "TypesEvenement.hpp"
=======
>>>>>>> e4b2b7a4a6a167874da7545d84df7b53f5ebf917
#include "../../structures/batiments/Batiment.hpp"
#include "../../structures/vaisseaux/Vaisseau.hpp"

/*
 * Classe qui permet d'affecter les vaisseaux
 * selon certains paramêtres
 */

class Evenement {
	
	public:
<<<<<<< HEAD
		Evenement(TypeEvenement::type typeEvenement, bool destructible = false, int _coutDeplacement = 1, int _multiplicateurDommage = 1, int _multiplicateurDegat = 1);
=======
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
>>>>>>> e4b2b7a4a6a167874da7545d84df7b53f5ebf917
		virtual void activer(Batiment* batiment) {}
		virtual void desactiver(Batiment* batiment) {}
		virtual void activer(Vaisseau* vaisseau) {}
		virtual void desactiver(Vaisseau* vaisseau) {}
<<<<<<< HEAD
		TypeEvenement::type quelType();
=======
		
		//Getters
		char* quelNom();
>>>>>>> e4b2b7a4a6a167874da7545d84df7b53f5ebf917
		bool estDestructible();
		bool estAccessible();
		bool tirPossible();
		bool ciblePossible();
		int getCoutDeplacement();
		int getMultiplicateurDommage();
		int getMultiplicateurDegat();
		
	private:
<<<<<<< HEAD
		// Nature de l'évènements.
		TypeEvenement::type typeEvenement;
=======
		// Nom de l'évènements.
		char* name;
>>>>>>> e4b2b7a4a6a167874da7545d84df7b53f5ebf917
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

<<<<<<< HEAD
const Evenement EvenementNuageGaz = Evenement(
	TypeEvenement::NuageGaz,
	false,
	1,
	2,
	1
);

const Evenement EvenementChampMeteor = Evenement(
	TypeEvenement::ChampMeteor,
	true,
	-1,
	1,
	1
);

const Evenement EvenementEpave = Evenement(
	TypeEvenement::Epave,
	true,
	-1,
	1,
	1
);

const Evenement EvenementInfluenceTrouNoir = Evenement(
	TypeEvenement::InfluenceTrouNoir,
	false,
	3,
	2,
	2
);

const Evenement EvenementStationSpatialeAbandonnee = Evenement(
	TypeEvenement::StationSpatialeAbandonnee,
	true,
	-1,
	1,
	1
);

#endif // EVENEMENT_HPP
=======
#endif // EVENEMENT_HPP
>>>>>>> e4b2b7a4a6a167874da7545d84df7b53f5ebf917

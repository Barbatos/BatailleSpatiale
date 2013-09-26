#ifndef EVENEMENT_HPP
#define EVENEMENT_HPP
#include <iostream>
#include <memory>
#include "TypeEvenement.hpp"
#include "../../structures/batiments/Batiment.hpp"
#include "../../structures/vaisseaux/Vaisseau.hpp"

/*
 * Classe qui permet d'affecter les vaisseaux
 * selon certains paramêtres
 */

class Evenement {
	public:
		Evenement(TypeEvenement typeEvenement, bool destructible = false, int _coutDeplacement = 1, int _multiplicateurDommage = 1, int _multiplicateurDegat = 1);
		virtual void activer(Batiment* batiment) {}
		virtual void desactiver(Batiment* batiment) {}
		virtual void activer(Vaisseau* vaisseau) {}
		virtual void desactiver(Vaisseau* vaisseau) {}
		TypeEvenement quelType();
		bool estDestructible();
		bool estAccessible();
		bool tirPossible();
		bool ciblePossible();
		int getCoutDeplacement();
		int getMultiplicateurDommage();
		int getMultiplicateurDegat();
		
	private:
		// Nature de l'évènements.
		TypeEvenement typeEvenement;
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

const Evenement NuageGaz = {
	NuageGaz,
	false,
	1,
	2,
	1
};

const Evenement ChampMeteor ={
	ChampMeteor,
	true,
	-1,
	1,
	1
};

const Evenement Epave ={
	Epave,
	true,
	-1,
	1,
	1
};

const Evenement InfluenceTrouNoir ={
	InfluenceTrouNoir,
	false,
	3,
	2,
	2
};

const Evenement StationSpatialeAbandonnee ={
	StationSpatialeAbandonnee,
	true,
	-1,
	1,
	1
};

#endif // EVENEMENT_HPP
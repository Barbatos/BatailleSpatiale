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
		Evenement(int _coutDeplacement = 1);
		virtual void activer(Batiment* batiment) {}
		virtual void desactiver(Batiment* batiment) {}
		virtual void activer(Vaisseau* vaisseau) {}
		virtual void desactiver(Vaisseau* vaisseau) {}
		bool accessible();
		int getCoutDeplacement();
	
	private:
		// nombre de deplacement a utiliser pour passer par cette case 1 par défaut -1 pour impossible
		int coutDeplacement;
};

typedef std::shared_ptr<Evenement> EvenementPtr;

#endif // EVENEMENT_HPP

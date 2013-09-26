#ifndef CELLULE_HPP
#define CELLULE_HPP
#include "TypeCellule.hpp"
#include "evenement/Evenement.hpp"
#include "../structures/batiments/TypeBatiment.hpp"
#include "../structures/batiments/Batiment.hpp"
#include "../structures/vaisseaux/Vaisseau.hpp"
#include "../structures/Structure.hpp"

/**
 * Cette classe est une case elementaire du plateau
 */
class Cellule{
	
	public:
		Cellule(EvenementPtr _evenement = 0, TypeCellule _type = CelluleVide);
		const TypeCellule getType();
		void setType(TypeCellule _type);
		const bool possedeEvenement();
		const bool possedeEmplacement(TypeCellule _type);
		const TypeCellule statutEmplacement();
		const int getCoutDeplacement();
		void subir(Structure const& attaquant);
		Structure getAttaquant();
		const TypeBatiment typeBatiment();
		const int distanceMaximale();
		const bool accessible();
		void retirerVaisseau();
		VaisseauPtr getVaisseau();
		void setVaisseau(VaisseauPtr _vaisseau);
		
		//Multiple fonctions de test
		void creerVaisseauTest();
		void creerVaisseauConstructeurTest();
		void creerBatimentBaseTest();
		
	protected:
		
	private:
		EvenementPtr evenement;
		BatimentPtr batiment;
		VaisseauPtr vaisseau;
		TypeCellule type;

};

#endif // CELLULE_HPP

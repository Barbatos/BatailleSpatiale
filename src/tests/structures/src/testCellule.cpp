#include <iostream>
#include "../../../serveur/plateau/CelluleServeur.hpp"
using namespace std;

int main() {

	// on cree trois cellules de tests
	CelluleServeur* c1, c2, c3;

	//on cree des vaisseaux et des batiments
	//VaisseauServeur(vieMax, bouclierMax, bouclierTaux, visibilite, attaque, distanceMax, consommation, type);
	VaisseauServeurPtr v1(320, 90, 55.0F, 50, 120, 90, 80, TypeVaisseau::Inexistant);
	VaisseauServeurPtr v2(120, 50, 15.0F, 20, 70, 50, 30, TypeVaisseau::Inexistant);
	//BatimentServeur(vieMax, bouclierMax, boclierTaux, visibilite, attaque, niveau, type);
	BatimentServeurPtr b1(100, 20, 15.0F, 10, 40, 1, TypeBatiment::Inexistant);
	BatimentServeurPtr b2(200, 80, 50.0F, 25, 80, 1, TypeBatiment::Inexistant);

	//on cree des evenements;



	//on affecte ces vaisseaux et batiments aux cellules
	c1->setVaisseau(v1);
	c2->setVaisseau(v2);
	c3->setBatiment(b1);

	// les choses suivantes ne devraient pas fonctionner :
	c1->setBatiment(b2); //la cellule ne peut avoir qu'une seule structure.

	//on teste les dégats infligés par les attaques;
	cout << "c2 avant attaque: " << endl << *c2 << endl;
	c1->attaquer(*c2);
	cout << "c2 après attaque: " << endl << *c2 << endl;


}

/*
void CelluleServeur::creerVaisseauTest() {
    vaisseau.reset(new VaisseauServeur(80, 20, 0.2f, 0, 20, 5, 25, TypeVaisseau::Simple));
}

void CelluleServeur::creerVaisseauConstructeurTest() {
    vaisseau.reset(new VaisseauServeur(40, 10, 0.1f, 0, 10, 10, 25, TypeVaisseau::Constructeur));
}

void CelluleServeur::creerBatimentBaseTest() {
    batiment.reset(new BatimentServeur(200, 50, 0.1f, 0, 0, 0, TypeBatiment::Base));
}
*/

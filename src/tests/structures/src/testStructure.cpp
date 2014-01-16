#include <iostream>
#include "../../structures/Structure.hpp"

using namespace std;

int main() {

	// On crée une technologie utile à la création des structures
	TechnologieStructure techS;

	// On crée trois structures
	Structure s1(100, 100, 0.5, 100, 100);
	Structure s2(200, 50, 0.7, 60, 150);
	Structure s3;

	// s1 subit une attaque de s2
	cout << "s1 : " << endl << s1 << endl;
	s1.subir(s2);
	cout << "s1 : " << endl << s1 << endl;

	cout << "s2 : " << endl << s2 << endl;
	s1.attaquer(s2);
	cout << "s2 : " << endl << s2 << endl;

	// s1 se soigne de 30 pv
	s1.modifierVie(+30);
	cout << "s1 : " << endl << s1 << endl;

	// Si l'on veut un système de degats bruts (qui ignorent le bouclier)
	s2.modifierVie(-50);
	cout << "s2 : " << endl << s2 << endl;

	//s3 a les attributs de s1 plus les améliorations dues aux technologies
	s3 = Structure::cloner(s1, techS);
	cout << "s3 : " << endl << s3 << endl;
}

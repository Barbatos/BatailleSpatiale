#include "global.hpp"

#ifndef SERVEUR
	//#include "client/fenetre.hpp"
#endif

void Frame()
{

#ifdef SERVEUR
	SV_Frame();
#else

	//@Charles - temporaire
	char temp[1337];
	int choix;

	cout << "Veuillez ecrire le paquet a envoyer au serveur : " << endl;
	cout << "	1 : Paquet de connexion au serveur" << endl;
	cout << "	2 : Paquet de deconnexion au serveur" << endl;

	cin >> temp;
	choix = atoi(temp);

#endif

	usleep(900000);
}

int main()
{
	return 0;
}

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

	/*switch(choix){
		case 1:
			sprintf(temp, "%d^CHELLO", CTS_CONNEXION);
			Network::Instance().EnvoyerPaquet("87.98.135.190", temp, strlen(temp));
			break;

		case 2:
			sprintf(temp, "%d^CBYE", CTS_DECONNEXION);
			Network::Instance().EnvoyerPaquet("87.98.135.190", temp, strlen(temp));
			break;
	}*/

#endif

	usleep(900000);
}

int main()
{
	#ifndef SERVEUR
	NetworkClient* client;

	client = new NetworkClient();
	#else
	unsigned int clientId;
	NetworkServer* server;
	server = new NetworkServer();

	while(1){
		if(server->acceptNewClient(clientId)){
			cout << "New client! " << clientId << endl;
		}
		usleep(500);
	}
	#endif
	/*Network::Instance().InitSocket();

	while (1)
    {
    	Frame();

        usleep(500);
    }

	Network::Instance().FermerSocket();
	*/
	return 0;
}

#ifndef _RESEAU_SERVER_H_
#define _RESEAU_SERVER_H_

#include "../global.hpp"
#include "../serveur/joueurs/Joueur.hpp"
#include "../core/ReseauGlobal.hpp"
#include "../core/enum/TypePaquet.hpp"

class ReseauServeur
{

	public:
		ReseauServeur(unsigned short port);
		~ReseauServeur(void);
		void AccepterNouveauClient(void);
		void TraiterPaquetClient(Joueur& joueur, sf::Uint16 typePaquet, string& msg);
		void TraiterCommandeClient(Joueur& joueur, string& command);
		void EnvoiATous(string& message);
		void EnvoiUnique(sf::TcpSocket& client, string& message);

	private:
		sf::TcpListener listener;
		sf::SocketSelector selector;

		vector<Joueur> joueurs;

};


#endif


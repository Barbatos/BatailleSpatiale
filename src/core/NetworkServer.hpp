#ifndef _NETWORK_SERVER_H_
#define _NETWORK_SERVER_H_

#include "../global.hpp"
#include "../serveur/joueurs/Joueur.hpp"
#include "../core/NetworkGlobal.hpp"

class NetworkServer
{

	public:
		NetworkServer(unsigned short port);
		~NetworkServer(void);
		void acceptNewClient(void);
		void ParseClientPacket(Joueur& joueur, int packetType, string& msg);
		void ParseClientCommand(Joueur& joueur, string& command);
		void SendToAll(string& message);

	private:
		sf::TcpListener listener;
		sf::SocketSelector selector;

		vector<Joueur> joueurs;

};


#endif

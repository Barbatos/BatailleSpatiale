#include "NetworkServer.hpp"

NetworkServer::NetworkServer(unsigned short port){

	// On écoute sur le port défini plus haut
	if (listener.listen(port) != sf::Socket::Done){
		cout << "[NETWORK] Impossible d'écouter sur le port " << port << endl;
		return;
	}

	// On met la socket en mode non-bloquant
	listener.setBlocking(false);

	// On ajoute la socket au selecteur
	selector.add(listener);

	cout << "[NETWORK] Ecoute sur le port " << port << " en cours..." << endl;
}

void NetworkServer::ParseClientCommand(Joueur& joueur, string& command){
	sf::TcpSocket* client = joueur.getSocket();

	// On récupère la commande exécutée
	string cmd = command.substr(0, command.find_first_of(' '));

	// Si c'est une commande pour changer de nom
	if((cmd == "/nick") || (cmd == "/name") || (cmd == "/pseudo")){

		if(command.size() < cmd.size() + 1){
			sf::Packet packet;
			string msg = "Vous devez entrer un nouveau pseudo !";
			packet << msg;
			NetworkGlobal::sendMessage(*client, packet);
			return;
		}

		// On récupère l'argument de la commande, à savoir le nouveau pseudo
		string newNick = command.substr(command.find_first_of(' ') + 1);

		// On remplace l'ancien pseudo par le nouveau et on avertit tout le monde
		if(!newNick.empty()){
			joueur.setPseudo(newNick);
			// TODO: avertir tlm
		}
	}
}

void NetworkServer::ParseClientPacket(Joueur& joueur, int packetType, string& msg){

	// Si le joueur a écrit du texte
	if(packetType == PACKETTYPE_CLIENT_SAY){
		
		// Si c'est une commande
		if(msg.at(0) == '/'){
			ParseClientCommand(joueur, msg);
		}
	}

	else {
		return;
	}
}

//void NetworkServer::SendToAll(){}

void NetworkServer::acceptNewClient(void)
{
	// On attend qu'il se passe quelque chose sur le réseau
	if (selector.wait()){

		// On teste s'il y a une nouvelle connexion en attente sur le serveur
		if (selector.isReady(listener)){
			// Nouveau client
			sf::TcpSocket* client = new sf::TcpSocket;
			sf::Packet send;
			string s = "Hello there!";
			send << s;

			// Le nouveau client a été accepté
			if (listener.accept(*client) == sf::Socket::Done){
				Joueur* j = new Joueur();

				j->setPseudo("Anonymous");
				j->setSocket(client);
				j->setId(1);

				// On ajoute le client à la liste des joueurs connectés
				joueurs.push_back(*j);

				// On ajoute également le client au selecteur afin qu'il puisse
				// recevoir ses messages
				selector.add(*client);

				// On envoie un paquet de bienvenue au client
				NetworkGlobal::sendMessage(*client, send);

				cout << "[NETWORK] Un nouveau client s'est connecte: " << client->getRemoteAddress() << ":" << client->getRemotePort() << endl;
			}

			// Le nouveau client a été refusé
			else {
				// On supprime la socket du client
				delete client;

				cout << "[NETWORK] Un nouveau client a tente de se connecter mais a ete rejete: " << client->getRemoteAddress() << endl;
			}
		}

		// Pas de nouvelle connexion, on vérifie si on a reçu un message 
		// d'un des clients
		else {
			// On parcours la liste de tous les clients
			for (vector<Joueur>::iterator it = joueurs.begin(); it != joueurs.end(); ++it){
				// On récupère les infos du client dans la liste
				Joueur& j = *it;
				sf::TcpSocket* client = j.getSocket();

				// Si le client a envoyé un message
				if (selector.isReady(*client)){
					sf::Packet packet;
					sf::Socket::Status status;

					status = client->receive(packet);

					// Le message s'est envoyé correctement
					if (status == sf::Socket::Done){
						string msg;
						int packetType;

						// On copie dans une variable le message reçu
						packet >> packetType >> msg;

						if(msg.empty()){
							return;
						}

						ParseClientPacket(j, packetType, msg);

						cout << "[NETWORK] Message du client " 
							 << j.getPseudo()
							 << " "
							 << client->getRemoteAddress() 
							 << ":" 
							 << client->getRemotePort() 
							 << " : " << packetType << " : " << msg << endl;

						return;
					}

					else {
						
						// Si c'est une déconnexion, on le fait savoir au serveur
						if(status == sf::Socket::Disconnected){
							cout << "[NETWORK] Le client " << client->getRemoteAddress() << " s'est deconnecte !" << endl;
						}

						// S'il y a eu une erreur lors de la réception du paquet
						if(status == sf::Socket::Error){
							cout << "[NETWORK] Erreur lors de la reception d'un paquet du client " << client->getRemoteAddress() << endl;
						}

						// On supprime le client du sélecteur
						selector.remove(*client);

						// On supprime le joueur de la liste
						joueurs.erase(it);
					}
				}
			}
		}
	}
}


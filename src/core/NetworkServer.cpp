#include "../global.hpp"

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

void NetworkServer::acceptNewClient(void)
{
	char welcomeMessage[] = "Bienvenue cher client !";

	// On attend qu'il se passe quelque chose sur le réseau
	if (selector.wait()){

		// On teste s'il y a une nouvelle connexion en attente sur le serveur
		if (selector.isReady(listener)){
			// Nouveau client
			sf::TcpSocket* client = new sf::TcpSocket;

			// Le nouveau client a été accepté
			if (listener.accept(*client) == sf::Socket::Done){
				// On ajoute le client à la liste des clients connectés
				clients.push_back(client);

				// On ajoute également le client au selecteur afin qu'il puisse
				// recevoir ses messages
				selector.add(*client);

				cout << "[NETWORK] Un nouveau client s'est connecte: " << client->getRemoteAddress() << endl;
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
			for (list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it){
				// On récupère les infos du client dans la liste
				sf::TcpSocket& client = **it;

				// Si le client a envoyé un message
				if (selector.isReady(client)){
					cout << "[NETWORK] Message recu du client: " << client.getRemoteAddress() << endl;
				}
			}
		}
	}











	// On attend une connexion
	/*if (listener.accept(socket) != sf::Socket::Done){
		return;
	}

	// Un client s'est connecté
	cout << "[NETWORK] Nouveau client: " << socket.getRemoteAddress() << endl;

	// On lui dit bonjour
	NetworkGlobal::sendMessage(socket, welcomeMessage);*/
}

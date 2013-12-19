#include "ReseauServeur.hpp"

ReseauServeur::ReseauServeur(unsigned short port, PlateauServeur& _plateau) : 
	plateau(_plateau), reseauThread(&ReseauServeur::threadReseau, this) {

	// On écoute sur le port défini plus haut
	if (listener.listen(port) != sf::Socket::Done){
		cout << "[RESEAU] Impossible d'écouter sur le port " << port << endl;
		return;
	}

	// On met la socket en mode non-bloquant
	listener.setBlocking(false);

	// On ajoute la socket au selecteur
	selector.add(listener);

	cout << "[RESEAU] Ecoute sur le port " << port << " en cours..." << endl;
}

void ReseauServeur::TraiterCommandeClient(JoueurServeur& joueur, string& commande){
	sf::TcpSocket* client = joueur.getSocket();

	// On récupère la commande exécutée
	string cmd = commande.substr(0, commande.find_first_of(' '));

	// Si c'est une commande pour changer de nom
	if((cmd == "/nick") || (cmd == "/name") || (cmd == "/pseudo")){

		if(commande.size() < cmd.size() + 2){
			string msg = "Vous devez entrer un nouveau pseudo !";
			EnvoiUnique(*client, msg);
			return;
		}

		// On récupère l'argument de la commande, à savoir le nouveau pseudo
		string newNick = commande.substr(commande.find_first_of(' ') + 1);

		// On remplace l'ancien pseudo par le nouveau et on avertit tout le monde
		if(!newNick.empty()){
			string msg = "Le joueur " + joueur.getPseudo() + " a change son pseudo en " + newNick;

			joueur.setPseudo(newNick);
			EnvoiATous(msg);
		}
	}

	// Retourne au client la liste des clients connectés
	else if((cmd == "/list") || (cmd == "/clients") || (cmd == "/players") || (cmd == "/joueurs")){
		string listeJoueurs = "Liste des joueurs connectés:\n";

		for (vector<JoueurServeur>::iterator it = joueurs.begin(); it != joueurs.end(); ++it){
			JoueurServeur& j = *it;
			ostringstream id;

			id << j.getId();

			listeJoueurs.append(j.getPseudo() + " (#" + id.str() + ")\n");
		}

		EnvoiUnique(*client, listeJoueurs);
	}

}

void ReseauServeur::TraiterPaquetClient(JoueurServeur& joueur, sf::Uint16 typePaquet, string& msg){

	switch(static_cast<TypePaquet>(typePaquet)){

		case TypePaquet::MessageEcho:

			// Si c'est une commande
			if(msg.at(0) == '/'){
				TraiterCommandeClient(joueur, msg);
			}

			// TEMP: sinon, on dit que c'est un message à envoyer à tout le monde
			else {
				string msgFinal;

				msgFinal = "<" + joueur.getPseudo() + "> " + msg;

				EnvoiATous(msgFinal);
			}

			break;

		// Le client veut changer de pseudo
		case TypePaquet::EnvoiPseudoServeur:

			break;

		default:
			cout << "[RESEAU] Erreur: paquet de type " << typePaquet << " inconnu" << endl;
			break;
	}
}

void ReseauServeur::EnvoiATous(string& message){
	sf::Packet paquet;
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::MessageEchoServeur);

	paquet << typePaquet << message;

	for (vector<JoueurServeur>::iterator it = joueurs.begin(); it != joueurs.end(); ++it){
		// On récupère les infos du client dans la liste
		JoueurServeur& j = *it;
		sf::TcpSocket* client = j.getSocket();

		ReseauGlobal::EnvoiPaquet(*client, paquet);
	}
}

void ReseauServeur::EnvoiUnique(sf::TcpSocket& client, string& message){
	sf::Packet paquet;
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::MessageEchoServeur);

	paquet << typePaquet << message;
	ReseauGlobal::EnvoiPaquet(client, paquet);
}

void ReseauServeur::EnvoiPlateau(sf::TcpSocket& client, PlateauServeur& plateau){
	sf::Packet paquet;
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Plateau);

	paquet << typePaquet << plateau;
	ReseauGlobal::EnvoiPaquet(client, paquet);
}


void ReseauServeur::EcouterReseau(void)
{

	// On attend qu'il se passe quelque chose sur le réseau
	if (selector.wait()){

		// On teste s'il y a une nouvelle connexion en attente sur le serveur
		if (selector.isReady(listener)){
			// Nouveau client
			sf::TcpSocket* client = new sf::TcpSocket;
			string s = "Salut ! Merci de changer ton pseudo avec la commande /nick <tonpseudo>";

			// Le nouveau client a été accepté
			if (listener.accept(*client) == sf::Socket::Done){
				JoueurServeur* j = new JoueurServeur();
				string msgGlobal;
				ostringstream c;

				j->setPseudo("Anonymous");
				j->setSocket(client);
				j->setId(joueurs.size()+1);

				// On ajoute le client à la liste des joueurs connectés
				joueurs.push_back(*j);

				// On ajoute également le client au selecteur afin qu'il puisse
				// recevoir ses messages
				selector.add(*client);

				// On envoie un paquet de bienvenue au client
				EnvoiUnique(*client, s);

				// On envoie le plateau
				EnvoiPlateau(*client, plateau);

				cout << "[RESEAU] Un nouveau client s'est connecte: " << client->getRemoteAddress() << ":" << client->getRemotePort() << endl;
				
				c << j->getId();

				msgGlobal = "Un nouveau joueur (#"  + c.str() + ") a rejoint le serveur";
				EnvoiATous(msgGlobal);


				delete j;
			}

			// Le nouveau client a été refusé
			else {
				// On supprime la socket du client
				delete client;

				cout << "[RESEAU] Un nouveau client a tente de se connecter mais a ete rejete: " << client->getRemoteAddress() << endl;
			}
		}

		// Pas de nouvelle connexion, on vérifie si on a reçu un message 
		// d'un des clients
		else {
			// On parcours la liste de tous les clients
			for (vector<JoueurServeur>::iterator it = joueurs.begin(); it != joueurs.end(); ++it){
				// On récupère les infos du client dans la liste
				JoueurServeur& j = *it;
				sf::TcpSocket* client = j.getSocket();

				// Si le client a envoyé un message
				if (selector.isReady(*client)){
					sf::Packet packet;
					sf::Socket::Status status;

					status = client->receive(packet);

					// Le message s'est envoyé correctement
					if (status == sf::Socket::Done){
						string msg;
						sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Vide);

						// On copie dans une variable le message reçu
						packet >> typePaquet >> msg;

						if(msg.empty()){
							return;
						}

						TraiterPaquetClient(j, typePaquet, msg);

						cout << "[RESEAU] Message du client " 
							 << j.getPseudo()
							 << " "
							 << client->getRemoteAddress() 
							 << ":" 
							 << client->getRemotePort() 
							 << " : " << typePaquet << " : " << msg << endl;

						return;
					}

					else {
						
						// Si c'est une déconnexion, on le fait savoir au serveur
						if(status == sf::Socket::Disconnected){
							string msgGlobal;
							ostringstream c;

							cout << "[RESEAU] Le client " << client->getRemoteAddress() << " s'est deconnecte !" << endl;

							c << j.getId();
							msgGlobal = j.getPseudo() + " (#"  + c.str() + ") s'est déconnecté du serveur";

							// On supprime le client du sélecteur
							selector.remove(*client);

							// On supprime le joueur de la liste
							joueurs.erase(it);

							// On envoie le message de déconnexion à tous les autres joueurs
							EnvoiATous(msgGlobal);
						}

						// S'il y a eu une erreur lors de la réception du paquet
						if(status == sf::Socket::Error){
							cout << "[RESEAU] Erreur lors de la reception d'un paquet du client " << client->getRemoteAddress() << endl;
						}
					}
				}
			}
		}
	}
}

void ReseauServeur::setPlateau(PlateauServeur& _plateau){
	plateau = _plateau;
}

void ReseauServeur::threadReseau(){
	while(true){
		EcouterReseau();
		sf::sleep(sf::milliseconds(100));
	}
}

void ReseauServeur::lancerReseau(){
	reseauThread.launch();
}

void ReseauServeur::fermerReseau(){
	reseauThread.terminate();
}


#include "ReseauServeur.hpp"

ReseauServeur::ReseauServeur(unsigned short port, PlateauServeur& _plateau) : 
	plateau(_plateau), reseauThread(&ReseauServeur::threadReseau, this), actif(false) {
        
    plateau.setJoueurs(&joueurs);

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

void ReseauServeur::traiterPaquetClient(JoueurServeur& joueur, sf::Packet paquet){
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Vide);
	sf::TcpSocket* client = joueur.getSocket();
	ostringstream id;
	Position pos, pos2;
	string msg;
	string msgFinal;

	paquet >> typePaquet;

	switch(static_cast<TypePaquet>(typePaquet)){

		// Message à envoyer à tout le monde
		case TypePaquet::MessageEcho:

			paquet >> msg;
			msgFinal = "<" + joueur.getPseudo() + "> " + msg;

			envoiATous(msgFinal);
			break;


		// Le client veut changer de pseudo
		case TypePaquet::ChangementDeNom:
			id << joueur.getId();

			paquet >> msg;
			msgFinal = "Le joueur " + joueur.getPseudo() + " (#" +id.str() + ") a change son pseudo en " + msg;

			joueur.setPseudo(msg);
			envoiATous(msgFinal);
			break;


		// Récupération de la liste des joueurs
		case TypePaquet::GetListeJoueurs:
			msgFinal = "Liste des joueurs connectés:\n";

			for (vector<JoueurServeur>::iterator it = joueurs.begin(); it != joueurs.end(); ++it){
				JoueurServeur& j = *it;
				ostringstream id;

				id << j.getId();

				msgFinal.append(j.getPseudo() + " (#" + id.str() + ")\n");
			}

			envoiUnique(*client, msgFinal);
			break;

		// Envoi de la zone parcourable au client
		case TypePaquet::GetZoneParcourable:
			paquet >> pos;
			envoiZoneParcourable(*client, pos);
			break;

		// Envoi au client du chemin entre un poont 1 et un point 2
		case TypePaquet::GetChemin:
			paquet >> pos >> pos2;
			envoiChemin(*client, pos, pos2);
			break;

		default:
			cout << "[RESEAU] Erreur: paquet de type " << typePaquet << " inconnu" << endl;
			break;
	}
}

void ReseauServeur::envoiATous(string& message){
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

void ReseauServeur::envoiUnique(sf::TcpSocket& client, string& message){
	sf::Packet paquet;
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::MessageEchoServeur);

	paquet << typePaquet << message;
	ReseauGlobal::EnvoiPaquet(client, paquet);
}

void ReseauServeur::envoiPlateau(sf::TcpSocket& client, PlateauServeur& plateau){
	sf::Packet paquet;
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Plateau);

	paquet << typePaquet << plateau;
	ReseauGlobal::EnvoiPaquet(client, paquet);
}

void ReseauServeur::envoiZoneParcourable(sf::TcpSocket& client, Position pos){
	sf::Packet paquet;
	std::list<NoeudServeur> noeuds;
	std::list<NoeudServeur>::iterator noeudIterator;
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::ZoneParcourable);
	sf::Int32 tailleZone;

	noeuds = plateau.getZoneParcourable(pos);

	tailleZone = noeuds.size();

	paquet << typePaquet << tailleZone;

	for (noeudIterator = noeuds.begin(); noeudIterator != noeuds.end(); noeudIterator++){
		paquet << noeudIterator->getPosition();
	}

	ReseauGlobal::EnvoiPaquet(client, paquet);
}

void ReseauServeur::envoiChemin(sf::TcpSocket& client, Position posDepart, Position posArrivee){
	sf::Packet paquet;
	std::list<NoeudServeur> noeuds;
	std::list<Position>::iterator cheminIterator;
	std::list<Position> chemin;
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Chemin);
	sf::Int32 tailleZone;

	noeuds = plateau.getZoneParcourable(posDepart);

	tailleZone = noeuds.size();

	chemin = PlateauServeur::obtenirChemin(posArrivee, noeuds);

	paquet << typePaquet << tailleZone;

	for(cheminIterator = chemin.begin(); cheminIterator != chemin.end(); cheminIterator++){
		paquet << *cheminIterator;
	}
}

void ReseauServeur::ecouterReseau(void)
{

	// On attend qu'il se passe quelque chose sur le réseau
	if (selector.wait(sf::milliseconds(50))){

		// On teste s'il y a une nouvelle connexion en attente sur le serveur
		if (selector.isReady(listener)){
			// Nouveau client
			sf::TcpSocket* client = new sf::TcpSocket;

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

				// On envoie le plateau
				envoiPlateau(*client, plateau);

				cout << "[RESEAU] Un nouveau client s'est connecte: " << client->getRemoteAddress() << ":" << client->getRemotePort() << endl;
				
				c << j->getId();

				msgGlobal = "Un nouveau joueur (#"  + c.str() + ") a rejoint le serveur";
				envoiATous(msgGlobal);


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
					sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Vide);
					sf::Packet packet;
					sf::Socket::Status status;

					status = client->receive(packet);

					// Le message s'est envoyé correctement
					if (status == sf::Socket::Done){
						string msg;

						if(msg.empty()){
							return;
						}

						traiterPaquetClient(j, packet);

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
							envoiATous(msgGlobal);
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
    plateau.setJoueurs(&joueurs);
}

void ReseauServeur::threadReseau(){
	while(actif){
		ecouterReseau();
		sf::sleep(sf::milliseconds(100));
	}
}

void ReseauServeur::lancerReseau(){
	actif = true;
	reseauThread.launch();
}

void ReseauServeur::fermerReseau(){
	actif = false;
}


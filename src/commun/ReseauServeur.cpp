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

void ReseauServeur::TraiterPaquetClient(JoueurServeur& joueur, sf::Uint16 typePaquet, string& msg){

	switch(static_cast<TypePaquet>(typePaquet)){

		// Message à envoyer à tout le monde
		case TypePaquet::MessageEcho:
			string msgFinal;

			msgFinal = "<" + joueur.getPseudo() + "> " + msg;

			EnvoiATous(msgFinal);
			break;


		// Le client veut changer de pseudo
		case TypePaquet::ChangementDeNom:
			ostringstream id;
			id << joueur.getId();

			string msgRetour = "Le joueur " + joueur.getPseudo() + " (#" +id.str() + ") a change son pseudo en " + msg;

			joueur.setPseudo(msg);
			EnvoiATous(msgRetour);
			break;


		// Récupération de la liste des joueurs
		case TypePaquet::GetListeJoueurs:
			string listeJoueurs = "Liste des joueurs connectés:\n";

			for (vector<JoueurServeur>::iterator it = joueurs.begin(); it != joueurs.end(); ++it){
				JoueurServeur& j = *it;
				ostringstream id;

				id << j.getId();

				listeJoueurs.append(j.getPseudo() + " (#" + id.str() + ")\n");
			}

			EnvoiUnique(*client, listeJoueurs);
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

void ReseauServeur::EnvoiZoneParcourable(sf::TcpSocket& client, sf::Int32 tailleZone, std::list<NoeudServeur> noeuds){
	sf::Packet paquet;
	sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::ZoneParcourable);
	std::list<NoeudServeur>::iterator noeudIterator;

	paquet << typePaquet << tailleZone;

	for (noeudIterator = noeuds.begin(); noeudIterator != noeuds.end(); noeudIterator++){
		paquet << noeudIterator->getPosition();
	}

	ReseauGlobal::EnvoiPaquet(client, paquet);
}

void ReseauServeur::EcouterReseau(void)
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
    plateau.setJoueurs(&joueurs);
}

void ReseauServeur::threadReseau(){
	while(actif){
		EcouterReseau();
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


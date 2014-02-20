#include <masterserveur/Master.hpp>

Master::Master(unsigned int portServeur, unsigned int portClient) {
    int nbEssais = 0;

    // Le Master écoute les connexions entrantes des différents serveurs de jeu
    while(listener.listen(portServeur) != sf::Socket::Done) {
        if(nbEssais >= 5) {
            cout << "[MASTER] Abandon de la tentative de lancement du serveur" << endl;
            return;
        }

        cout << "[MASTER] Impossible d'écouter sur le port " << portServeur << ", essai sur le port " << (portServeur+1) << endl;

        portServeur++;
        nbEssais++;
    }

    cout << "[MASTER] Ecoute sur le port (serveurs) " << portServeur << " en cours..." << endl;

    nbEssais = 0;

    // Le master écoute également les connexions entrantes de joueurs voulant récupérer la liste des serveurs
    while(listenerClients.listen(portClient) != sf::Socket::Done) {
        if(nbEssais >= 5) {
            cout << "[MASTER] Abandon de la tentative de lancement du serveur" << endl;
            return;
        }

        cout << "[MASTER] Impossible d'écouter sur le port " << portClient << ", essai sur le port " << (portClient+1) << endl;

        portClient++;
        nbEssais++;
    }


    // On met la socket en mode non-bloquant
    listener.setBlocking(false);
    listenerClients.setBlocking(false);

    // On ajoute la socket au selecteur
    selector.add(listener);
    selector.add(listenerClients);

    cout << "[MASTER] Ecoute sur le port (clients) " << portClient << " en cours..." << endl;
}

void Master::ecouterReseau() {

    // On attend qu'il se passe quelque chose sur le réseau
    if (selector.wait(sf::milliseconds(100))) {

        // On teste s'il y a une nouvelle connexion en attente sur le serveur
        if (selector.isReady(listener)) {
            // Nouveau serveur
            sf::TcpSocket* serveur = new sf::TcpSocket;

            // Le nouveau serveur a été accepté
            if (listener.accept(*serveur) == sf::Socket::Done) {
                ServeurMaster* sv;
                string msgGlobal;
                ostringstream c;

                sv = new ServeurMaster();
                sv->setIp(serveur->getRemoteAddress());
                sv->setPort(serveur->getRemotePort());
                sv->setSocket(serveur);
                sv->setId(serveurs.size()+1);
                sv->setDernierHeartbeat(timer.getElapsedTime());

                // On ajoute le serveur à la liste des serveurs connectés
                serveurs.push_back(*sv);

                // On ajoute également le serveur au selecteur afin qu'il puisse
                // recevoir ses messages
                selector.add(*serveur);

                cout << "[MASTER] Un nouveau serveur s'est connecte: " << serveur->getRemoteAddress() << ":" << serveur->getRemotePort() << endl;

                delete sv;
            }

            // Le nouveau serveur a été refusé
            else {
                // On supprime la socket du serveur
                delete serveur;

                cout << "[MASTER] Un nouveau serveur a tente de se connecter mais a ete rejete: " << serveur->getRemoteAddress() << endl;
            }
        }

        else if(selector.isReady(listenerClients)) {
            // Nouveau client
            sf::TcpSocket* client = new sf::TcpSocket;

            // Le nouveau client a été accepté
            if (listenerClients.accept(*client) == sf::Socket::Done) {
                ClientMaster* cl;
                string msgGlobal;
                ostringstream c;

                cl = new ClientMaster();
                cl->setIp(client->getRemoteAddress());
                cl->setPort(client->getRemotePort());
                cl->setSocket(client);
                cl->setId(clients.size()+1);

                // On ajoute le client à la liste des clients connectés
                clients.push_back(*cl);

                // On ajoute également le client au selecteur afin qu'il puisse
                // recevoir ses messages
                selector.add(*client);

                cout << "[MASTER] Un nouveau client s'est connecte: " << client->getRemoteAddress() << ":" << client->getRemotePort() << endl;

                envoiListeServeursAll();

                delete cl;
            }

            // Le nouveau serveur a été refusé
            else {
                // On supprime la socket du serveur
                delete client;

                cout << "[MASTER] Un nouveau client a tente de se connecter mais a ete rejete: " << client->getRemoteAddress() << endl;
            }
        }

        // Pas de nouvelle connexion, on vérifie si on a reçu un message
        // d'un des serveurs ou clients
        else {
            // On parcours la liste de tous les serveurs
            for (vector<ServeurMaster>::iterator it = serveurs.begin(); it != serveurs.end();) {
                // On récupère les infos du serveur dans la liste
                ServeurMaster& sv = *it;
                sf::TcpSocket* serveur = sv.getSocket();

                // Si le serveur a envoyé un message
                if (selector.isReady(*serveur)) {
                    sf::Packet packet;
                    sf::Socket::Status status;

                    status = serveur->receive(packet);

                    // Le message s'est envoyé correctement
                    if (status == sf::Socket::Done) {

                        traiterPaquetServeur(sv, packet);

                        cout << "[MASTER] Message du serveur "
                             << sv.getId()
                             << " "
                             << serveur->getRemoteAddress()
                             << ":"
                             << serveur->getRemotePort()
                             << endl;

                        return;
                    }

                    else {

                        // Si c'est une déconnexion, on le fait savoir au master serveur
                        if(status == sf::Socket::Disconnected) {

                            cout << "[MASTER] Le serveur " << serveur->getRemoteAddress() << " s'est deconnecte !" << endl;

                            // On supprime le serveur du sélecteur
                            selector.remove(*serveur);

                            // On supprime le serveur de la liste
                            it = serveurs.erase(it);

                            continue;
                        }

                        // S'il y a eu une erreur lors de la réception du paquet
                        if(status == sf::Socket::Error) {
                            cout << "[MASTER] Erreur lors de la reception d'un paquet du serveur " << serveur->getRemoteAddress() << endl;
                        }
                    }
                }
                ++it;
            }

            // On parcours la liste de tous les clients
            for (vector<ClientMaster>::iterator it = clients.begin(); it != clients.end();) {
                // On récupère les infos du client dans la liste
                ClientMaster& cl = *it;
                sf::TcpSocket* client = cl.getSocket();

                // Si le client a envoyé un message
                if (selector.isReady(*client)) {
                    sf::Packet packet;
                    sf::Socket::Status status;

                    status = client->receive(packet);

                    // Le message s'est envoyé correctement
                    if (status == sf::Socket::Done) {

                        traiterPaquetClient(cl, packet);

                        cout << "[MASTER] Message du client "
                             << cl.getId()
                             << " "
                             << client->getRemoteAddress()
                             << ":"
                             << client->getRemotePort()
                             << endl;

                        return;
                    }

                    else {

                        // Si c'est une déconnexion, on le fait savoir au master serveur
                        if(status == sf::Socket::Disconnected) {

                            cout << "[MASTER] Le client " << client->getRemoteAddress() << " s'est deconnecte !" << endl;

                            // On supprime le client du sélecteur
                            selector.remove(*client);

                            // On supprime le client de la liste
                            it = clients.erase(it);
                            continue;
                        }

                        // S'il y a eu une erreur lors de la réception du paquet
                        if(status == sf::Socket::Error) {
                            cout << "[MASTER] Erreur lors de la reception d'un paquet du client " << client->getRemoteAddress() << endl;
                        }
                    }
                }
                ++it;
            }
        }
    }
}

void Master::verifierServeursActifs() {
    sf::Time tempsEcoule;

    tempsEcoule = timer.getElapsedTime();

    for (vector<ServeurMaster>::iterator it = serveurs.begin(); it != serveurs.end(); ++it) {
        ServeurMaster& sv = *it;
        sf::TcpSocket* serveur = sv.getSocket();

        // Les serveurs envoient des heartbeats toutes les minutes, si ça fait plus de trois 
        // minutes que l'on n'a rien reçu, on vire le serveur.
        if((tempsEcoule.asSeconds() - sv.getDernierHeartbeat().asSeconds()) > 180) {
            cout << "[MASTER] Le serveur " << serveur->getRemoteAddress() << " a timeout." << endl;

            // On supprime le serveur du sélecteur
            selector.remove(*serveur);

            // On supprime le serveur de la liste
            serveurs.erase(it);
        }
    }
}

void Master::traiterPaquetServeur(ServeurMaster& serveur, sf::Packet paquet) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Vide);
    string msg;

    paquet >> typePaquet;

    switch(static_cast<TypePaquet>(typePaquet)) {

            // Message heartbeat d'un serveur de jeu
        case TypePaquet::MasterHeartbeat:
            majServeur(paquet, serveur);
            break;

            // Message de déconnexion d'un serveur de jeu
        case TypePaquet::MasterDeconnexion:
            supprimerServeur(serveur);
            break;

        default:
            cout << "[MASTER] Erreur: paquet de type " << typePaquet << " inconnu" << endl;
            break;
    }
}

void Master::traiterPaquetClient(ClientMaster& client, sf::Packet paquet) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Vide);
    string msg;

    paquet >> typePaquet;

    switch(static_cast<TypePaquet>(typePaquet)) {

            // Message d'un client qui demande la liste des serveurs
        case TypePaquet::MasterGetServeurs:
            envoiListeServeurs(client);
            break;

        default:
            cout << "[MASTER] Erreur: paquet de type " << typePaquet << " inconnu" << endl;
            break;
    }
}

void Master::majServeur(sf::Packet paquet, ServeurMaster& serveur) {
    unsigned short port;
    string nom;

    paquet >> port >> nom; 

    serveur.setDernierHeartbeat(timer.getElapsedTime());
    serveur.setPort(port);
    serveur.setNom(nom);

    cout << "[MASTER] Heartbeat recu du serveur " << serveur.getNom() << " " << serveur.getIp() << ":" << serveur.getPort() << endl;
}

void Master::supprimerServeur(ServeurMaster& serveur) {
    sf::TcpSocket* sock = serveur.getSocket();

    for (vector<ServeurMaster>::iterator it = serveurs.begin(); it != serveurs.end(); ++it) {
        ServeurMaster& sv = *it;

        if(sv.getId() == serveur.getId()){
            selector.remove(*sock);
            serveurs.erase(it);
        }
    }

    envoiListeServeursAll();
}

void Master::envoiListeServeurs(ClientMaster& client) {
    sf::TcpSocket* cl = client.getSocket();
    sf::Packet paquet;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::MasterListeServeurs);
    sf::Int32 nbServeurs;

    nbServeurs = serveurs.size();

    paquet << typePaquet << nbServeurs;

    for (vector<ServeurMaster>::iterator it = serveurs.begin(); it != serveurs.end(); ++it) {
        paquet << *it;
    }

    ReseauGlobal::EnvoiPaquet(*cl, paquet);
}

void Master::envoiListeServeursAll() {
    for (vector<ClientMaster>::iterator it = clients.begin(); it != clients.end(); ++it) {
        ClientMaster& cl = *it;

        envoiListeServeurs(cl);
    }
}

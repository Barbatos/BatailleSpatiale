#include "ReseauServeur.hpp"

ReseauServeur::ReseauServeur(unsigned short port, PlateauServeur& _plateau) :
    plateau(_plateau), reseauThread(&ReseauServeur::threadReseau, this), actif(false) {
    int nbEssais = 0;
    unsigned short portMaster = 1500;
    sf::IpAddress masterServer("barbatos.fr");
    sf::Time timeout = sf::seconds(2);

    plateau.setJoueurs(&joueurs);

    // On écoute sur le port défini plus haut
    while(listener.listen(port) != sf::Socket::Done) {
        if(nbEssais >= 5) {
            cout << "[RESEAU] Abandon de la tentative de lancement du serveur" << endl;
            return;
        }

        cout << "[RESEAU] Impossible d'écouter sur le port " << port << ", essai sur le port " << (port+1) << endl;

        port++;
        nbEssais++;
    }

    nbEssais = 0;

    // On tente de se connecter au Master Serveur
    while(socketMaster.connect(masterServer, portMaster, timeout) != sf::Socket::Done) {
        if(nbEssais >= 5) {
            cout << "[RESEAU] Abandon de la tentative de connexion au Master Serveur" << endl;
            break;
        }

        cout << "[RESEAU] Impossible de se connecter au Master Serveur sur le port " << portMaster << ", essai sur le port " << (portMaster+1) << endl;

        portMaster++;
        nbEssais++;
    }

    // On met la socket en mode non-bloquant
    listener.setBlocking(false);
    socketMaster.setBlocking(false);

    // On ajoute la socket au selecteur
    selector.add(listener);

    dernierHeartbeat = timer.getElapsedTime();

    cout << "[RESEAU] Ecoute sur le port " << port << " en cours..." << endl;
}

void ReseauServeur::traiterPaquetClient(JoueurServeur& joueur, sf::Packet paquet) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Vide);
    sf::TcpSocket* client = joueur.getSocket();
    ostringstream id;
    Position pos, pos2;
    string msg;
    string msgFinal;

    paquet >> typePaquet;

    switch(static_cast<TypePaquet>(typePaquet)) {

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

        // Récupération des infos du joueur courant
    case TypePaquet::GetJoueurCourant:
        envoiJoueurCourant(joueur);

        // Récupération de la liste des joueurs
    case TypePaquet::GetJoueursAdverses:
        envoiJoueursAdverses(joueur);
        break;

        // Envoi de la zone parcourable au client
    case TypePaquet::GetZoneParcourable:
        paquet >> pos;
        envoiZoneParcourable(*client, pos);
        break;

        // Envoi au client du chemin entre un point 1 et un point 2
    case TypePaquet::GetChemin:
        paquet >> pos >> pos2;
        envoiChemin(*client, pos, pos2);
        break;


        // Le client demande à déplacer un vaisseau
    case TypePaquet::DemanderDeplacementVaisseau:
        paquet >> pos >> pos2;
        deplacerVaisseau(*client, pos, pos2, joueur);
        break;

        // Le client demande la zone constructible autour d'un point
    case TypePaquet::GetZoneConstructibleVaisseau:
        paquet >> pos;
        envoiZoneConstructibleVaisseau(joueur);
        break;

        // Le client demande la zone constructible autour d'un point
    case TypePaquet::GetZoneConstructibleBatiment:
        paquet >> pos;
        envoiZoneConstructibleBatiment(joueur, pos);
        break;

        // Le client demande la zone attaquable
    case TypePaquet::GetZoneAttaquable:
        paquet >> pos;
        envoiZoneAttaquable(*client, pos);
        break;

        // Le client demande à attaquer un vaisseau adverse
    case TypePaquet::DemanderAttaqueVaisseau:
        paquet >> pos >> pos2;
        attaquerVaisseau(*client, pos, pos2);
        break;

    default:
        cout << "[RESEAU] Erreur: paquet de type " << typePaquet << " inconnu" << endl;
        break;
    }
}

void ReseauServeur::envoiATous(string& message) {
    sf::Packet paquet;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::MessageEchoServeur);

    paquet << typePaquet << message;

    for (vector<JoueurServeur>::iterator it = joueurs.begin(); it != joueurs.end(); ++it) {
        // On récupère les infos du client dans la liste
        JoueurServeur& j = *it;
        sf::TcpSocket* client = j.getSocket();

        ReseauGlobal::EnvoiPaquet(*client, paquet);
    }
}

void ReseauServeur::envoiUnique(sf::TcpSocket& client, string& message) {
    sf::Packet paquet;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::MessageEchoServeur);

    paquet << typePaquet << message;
    ReseauGlobal::EnvoiPaquet(client, paquet);
}

void ReseauServeur::envoiPlateau(sf::TcpSocket& client, PlateauServeur& plateau) {
    sf::Packet paquet;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Plateau);

    paquet << typePaquet << plateau;
    ReseauGlobal::EnvoiPaquet(client, paquet);
}

void ReseauServeur::envoiPlateauATous() {
    sf::Packet paquet;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Plateau);

    paquet << typePaquet << plateau;

    for (vector<JoueurServeur>::iterator it = joueurs.begin(); it != joueurs.end(); ++it) {
        // On récupère les infos du client dans la liste
        JoueurServeur& j = *it;
        sf::TcpSocket* client = j.getSocket();

        ReseauGlobal::EnvoiPaquet(*client, paquet);
    }
}

void ReseauServeur::envoiZoneParcourable(sf::TcpSocket& client, Position pos) {
    sf::Packet paquet;
    std::list<NoeudServeur> noeuds;
    std::list<NoeudServeur>::iterator noeudIterator;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::ZoneParcourable);
    sf::Int32 tailleZone;

    noeuds = plateau.getZoneParcourable(pos);

    tailleZone = noeuds.size();

    paquet << typePaquet << tailleZone;

    for (noeudIterator = noeuds.begin(); noeudIterator != noeuds.end(); noeudIterator++) {
        paquet << noeudIterator->getPosition();
    }

    ReseauGlobal::EnvoiPaquet(client, paquet);
}

void ReseauServeur::envoiJoueurCourant(JoueurServeur& joueur) {
    sf::Packet paquet;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::JoueurCourant);
    sf::TcpSocket* client = joueur.getSocket();

    paquet << typePaquet << joueur;

    ReseauGlobal::EnvoiPaquet(*client, paquet);
}

void ReseauServeur::envoiJoueursAdverses(JoueurServeur& joueur) {
    sf::Packet paquet;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::JoueursAdverses);
    sf::TcpSocket* client = joueur.getSocket();

    paquet << typePaquet << (sf::Int32) joueurs.size() - 1;

    for (vector<JoueurServeur>::iterator j = joueurs.begin(); j != joueurs.end(); ++j) {
        if(j->getId() != joueur.getId())
            paquet << j->getPseudo();
    }

    ReseauGlobal::EnvoiPaquet(*client, paquet);
}

void ReseauServeur::envoiChemin(sf::TcpSocket& client, Position posDepart, Position posArrivee) {
    sf::Packet paquet;
    std::list<NoeudServeur> noeuds;
    std::list<Position>::iterator cheminIterator;
    std::list<Position> chemin;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Chemin);
    sf::Int32 tailleChemin;

    noeuds = plateau.getZoneParcourable(posDepart);

    chemin = PlateauServeur::obtenirChemin(posArrivee, noeuds);

    tailleChemin = chemin.size();

    paquet << typePaquet << tailleChemin;

    for(cheminIterator = chemin.begin(); cheminIterator != chemin.end(); cheminIterator++) {
        paquet << *cheminIterator;
    }

    ReseauGlobal::EnvoiPaquet(client, paquet);
}

void ReseauServeur::deplacerVaisseau(sf::TcpSocket& client, Position posDepart, Position posArrivee, JoueurServeur& joueur) {
    sf::Packet paquet;
    sf::Uint16 paquetDeplacerVaisseau = static_cast<sf::Uint16>(TypePaquet::DeplacerVaisseau);
    sf::Uint16 paquetDeplacementImpossible = static_cast<sf::Uint16>(TypePaquet::DeplacementVaisseauImpossible);

    if(plateau.deplacerVaisseau(posDepart, posArrivee, plateau.getZoneParcourable(posDepart), joueur)) {
        paquet << paquetDeplacerVaisseau;
        envoiPlateauATous();
    } else {
        paquet << paquetDeplacementImpossible;
    }

    ReseauGlobal::EnvoiPaquet(client, paquet);
}

void ReseauServeur::attaquerVaisseau(sf::TcpSocket& client, Position posAttaquant, Position posCible) {
    sf::Packet paquet;
    sf::Uint16 paquetAttaquerVaisseau = static_cast<sf::Uint16>(TypePaquet::AttaquerVaisseau);
    sf::Uint16 paquetAttaqueImpossible = static_cast<sf::Uint16>(TypePaquet::AttaqueVaisseauImpossible);
    CelluleServeur cAttaquant, cCible;

    cAttaquant = plateau.cellule[posAttaquant.x][posAttaquant.y];
    cCible = plateau.cellule[posCible.x][posCible.y];

    // TODO : check dans attaquer() que l'on a bien le droit d'attaquer la cellule cible !
    /*if(cAttaquant.attaquer(&cCible)) {
        paquet << paquetAttaquerVaisseau;
        envoiPlateauATous();
    } else {
        paquet << paquetAttaqueImpossible;
    }*/

    cAttaquant.attaquer(&cCible);
    paquet << paquetAttaquerVaisseau;
    envoiPlateauATous();
    
    ReseauGlobal::EnvoiPaquet(client, paquet);
}

void ReseauServeur::envoiZoneConstructibleVaisseau(JoueurServeur& joueur) {
    sf::Packet paquet;
    sf::TcpSocket* client = joueur.getSocket();
    std::list<Position> listePos;
    std::list<Position>::iterator pos;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::ZoneConstructibleVaisseau);
    sf::Int32 tailleZone;

    listePos = plateau.getZoneConstructibleVaisseau(joueur.getId());

    tailleZone = listePos.size();

    paquet << typePaquet << tailleZone;

    for (pos = listePos.begin(); pos != listePos.end(); pos++) {
        paquet << *pos;
    }

    ReseauGlobal::EnvoiPaquet(*client, paquet);
}

void ReseauServeur::envoiZoneConstructibleBatiment(JoueurServeur& joueur, Position p) {
    sf::Packet paquet;
    sf::TcpSocket* client = joueur.getSocket();
    std::list<Position> listePos;
    std::list<Position>::iterator pos;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::ZoneConstructibleBatiment);
    sf::Int32 tailleZone;

    listePos = plateau.getZoneConstructibleBatiment(p, joueur.getId());

    tailleZone = listePos.size();

    paquet << typePaquet << tailleZone;

    for (pos = listePos.begin(); pos != listePos.end(); pos++) {
        paquet << *pos;
    }

    ReseauGlobal::EnvoiPaquet(*client, paquet);
}

void ReseauServeur::envoiZoneAttaquable(sf::TcpSocket& client, Position p) {
    sf::Packet paquet;
    std::list<NoeudServeur> noeuds;
    std::list<NoeudServeur>::iterator noeudIterator;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::ZoneAttaquable);
    sf::Int32 tailleZone;

    noeuds = plateau.getZoneAttaquable(p);

    tailleZone = noeuds.size();

    paquet << typePaquet << tailleZone;

    for (noeudIterator = noeuds.begin(); noeudIterator != noeuds.end(); noeudIterator++) {
        paquet << noeudIterator->getPosition();
    }

    ReseauGlobal::EnvoiPaquet(client, paquet);
}

void ReseauServeur::creerBase(JoueurServeur& joueur, int nbJoueurs) {
    sf::Int32 posX;
    sf::Int32 posY;

    if(nbJoueurs == 1) {
        posX = 2;
        posY = 2;
        
        plateau.cellule[6][4].creerVaisseauTest(TypeVaisseau::Destructeur);
        joueur.ajouterVaisseau(plateau.cellule[6][4].getVaisseau());
        plateau.cellule[8][5].creerVaisseauTest(TypeVaisseau::Leger);
        joueur.ajouterVaisseau(plateau.cellule[8][5].getVaisseau());
    }
    else {
        posX = plateau.getTailleX() - 2;
        posY = plateau.getTailleY() - 2;
        plateau.cellule[7][6].creerVaisseauTest(TypeVaisseau::Constructeur);
        joueur.ajouterVaisseau(plateau.cellule[7][6].getVaisseau());
        plateau.cellule[5][1].creerVaisseauTest();
        joueur.ajouterVaisseau(plateau.cellule[5][1].getVaisseau());
    }

    plateau.cellule[posX][posY].creerBatimentBase();
    joueur.ajouterBatiment(plateau.cellule[posX][posY].getBatiment());
}

void ReseauServeur::ecouterReseau(void) {

    // On attend qu'il se passe quelque chose sur le réseau
    if (selector.wait(sf::milliseconds(50))) {

        // On teste s'il y a une nouvelle connexion en attente sur le serveur
        if (selector.isReady(listener)) {
            // Nouveau client
            sf::TcpSocket* client = new sf::TcpSocket;

            // Le nouveau client a été accepté
            if (listener.accept(*client) == sf::Socket::Done) {
                JoueurServeur* j;
                string msgGlobal;
                ostringstream c;

                if(joueurs.size() >= 2) {
                    // On supprime la socket du client
                    delete client;

                    cout << "[RESEAU] Client refuse: la partie est complete. " << client->getRemoteAddress() << endl;
                    return;
                }

                j = new JoueurServeur();
                j->setPseudo("Anonymous");
                j->setSocket(client);
                j->setId(joueurs.size()+1);

                // On ajoute le client à la liste des joueurs connectés
                joueurs.push_back(*j);

                // On ajoute également le client au selecteur afin qu'il puisse
                // recevoir ses messages
                selector.add(*client);

                // On crée la base du joueur
                creerBase(*j, joueurs.size());

                // On envoie le plateau à tous les joueurs
                envoiPlateauATous();

                // On envoie ses infos au joueur
                envoiJoueurCourant(*j);

                // On envoie la liste des joueurs adverses
                envoiJoueursAdverses(*j);

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
            for (vector<JoueurServeur>::iterator it = joueurs.begin(); it != joueurs.end();) {
                // On récupère les infos du client dans la liste
                JoueurServeur& j = *it;
                sf::TcpSocket* client = j.getSocket();

                // Si le client a envoyé un message
                if (selector.isReady(*client)) {
                    sf::Packet packet;
                    sf::Socket::Status status;

                    status = client->receive(packet);

                    // Le message s'est envoyé correctement
                    if (status == sf::Socket::Done) {

                        traiterPaquetClient(j, packet);

                        cout << "[RESEAU] Message du client "
                             << j.getPseudo()
                             << " "
                             << client->getRemoteAddress()
                             << ":"
                             << client->getRemotePort()
                             << endl;

                        return;
                    }

                    else {

                        // Si c'est une déconnexion, on le fait savoir au serveur
                        if(status == sf::Socket::Disconnected) {
                            string msgGlobal;
                            ostringstream c;

                            cout << "[RESEAU] Le client " << client->getRemoteAddress() << " s'est deconnecte !" << endl;

                            c << j.getId();
                            msgGlobal = j.getPseudo() + " (#"  + c.str() + ") s'est déconnecté du serveur";

                            // On supprime le client du sélecteur
                            selector.remove(*client);

                            // On supprime le joueur de la liste
                            it = joueurs.erase(it);

                            // On envoie le message de déconnexion à tous les autres joueurs
                            envoiATous(msgGlobal);

                            continue;
                        }

                        // S'il y a eu une erreur lors de la réception du paquet
                        if(status == sf::Socket::Error) {
                            cout << "[RESEAU] Erreur lors de la reception d'un paquet du client " << client->getRemoteAddress() << endl;
                        }
                    }
                }
                ++it;
            }
        }
    }

    envoiHeartbeat();
}

void ReseauServeur::setPlateau(PlateauServeur& _plateau) {
    plateau = _plateau;
    plateau.setJoueurs(&joueurs);
}

void ReseauServeur::threadReseau() {
    while(actif) {
        ecouterReseau();

        sf::sleep(sf::milliseconds(100));
    }
}

void ReseauServeur::lancerReseau() {
    actif = true;
    reseauThread.launch();
}

void ReseauServeur::fermerReseau() {
    actif = false;

    selector.clear();
    listener.close();
    socketMaster.disconnect();
}

void ReseauServeur::envoiHeartbeat() {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::MasterHeartbeat);
    sf::Time tempsEcoule;
    sf::Packet paquet;

    tempsEcoule = timer.getElapsedTime();

    if((tempsEcoule.asSeconds() - dernierHeartbeat.asSeconds()) < 60) {
        return;
    } 

    paquet << typePaquet;

    dernierHeartbeat = tempsEcoule;

    cout << "[RESEAU] Envoi d'un heartbeat au Master Serveur" << endl;

    ReseauGlobal::EnvoiPaquet(socketMaster, paquet);
}

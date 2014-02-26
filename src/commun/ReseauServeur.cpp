#include "ReseauServeur.hpp"

ReseauServeur::ReseauServeur(unsigned short _port, PlateauServeur& _plateau, string _nom, bool _partieSolo) :
    plateau(_plateau), reseauThread(&ReseauServeur::threadReseau, this), nom(_nom), actif(false), port(_port), partieSolo(_partieSolo) {
    int nbEssais = 0;
    unsigned short portMaster = 1500;
    sf::IpAddress masterServer("barbatos.fr");
    sf::Time timeout = sf::seconds(0.1);

    plateau.setJoueurs(&joueurs);
    joueurActuel = -1;
    masterActif = true;

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

    if(!partieSolo) {
        // On tente de se connecter au Master Serveur
        while(socketMaster.connect(masterServer, portMaster, timeout) != sf::Socket::Done) {
            if(nbEssais >= 5) {
                cout << "[RESEAU] Abandon de la tentative de connexion au Master Serveur" << endl;
                masterActif = false;
                break;
            }

            cout << "[RESEAU] Impossible de se connecter au Master Serveur sur le port " << portMaster << ", essai sur le port " << (portMaster+1) << endl;

            portMaster++;
            nbEssais++;
        }

        socketMaster.setBlocking(false);
        dernierHeartbeat = timer.getElapsedTime() - sf::seconds(60);
    }

    // On met la socket en mode non-bloquant
    listener.setBlocking(false);

    // On ajoute la socket au selecteur
    selector.add(listener);

    cout << "[RESEAU] Ecoute sur le port " << port << " en cours..." << endl;
}

void ReseauServeur::traiterPaquetClient(JoueurServeur& joueur, sf::Packet paquet) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Vide);
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

        // On envoie ses infos au joueur
        envoiJoueurCourant(joueur);
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
        envoiZoneParcourable(joueur, pos);
        break;

        // Envoi au client du chemin entre un point 1 et un point 2
    case TypePaquet::GetChemin:
        paquet >> pos >> pos2;
        envoiChemin(joueur, pos, pos2);
        break;


        // Le client demande à déplacer un vaisseau
    case TypePaquet::DemanderDeplacementVaisseau:
        paquet >> pos >> pos2;
        deplacerVaisseau(joueur, pos, pos2);
        envoiZoneVisible(joueur);
        break;

        // Le client demande la zone constructible autour d'un point
    case TypePaquet::GetZoneConstructibleVaisseau:
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
        envoiZoneAttaquable(joueur, pos);
        break;

        // Le client demande à attaquer un vaisseau adverse
    case TypePaquet::DemanderAttaqueVaisseau:
        paquet >> pos >> pos2;
        attaquerVaisseau(joueur, pos, pos2);
        break;

        // Le client demande la liste des vaisseaux constructibles
    case TypePaquet::GetVaisseauxConstructibles:
        envoiVaisseauxConstructibles(joueur);
        break;

        // Le client demande la liste des batiments constructibles depuis un vaisseau constructeur
    case TypePaquet::GetBatimentsConstructibles:
        paquet >> pos;
        envoiBatimentsConstructibles(joueur, pos);
        break;

        // Le client demande la zone visible
    case TypePaquet::GetZoneVisible:
        envoiZoneVisible(joueur);
        break;

        // Le client demande à ce que son tour se termine
    case TypePaquet::DemanderFinTour:
        joueurSuivant();
        break;

        // Le client demande la construction d'un vaisseau
    case TypePaquet::DemanderConstructionVaisseau:
        construireVaisseau(joueur, paquet);
        break;

        // Le client demande la construction d'un batiment
    case TypePaquet::DemanderConstructionBatiment:
        construireBatiment(joueur, paquet);
        break;

    default:
        cout << "[RESEAU] Erreur: paquet de type " << typePaquet << " inconnu" << endl;
        break;
    }
}

void ReseauServeur::envoiPaquet(JoueurServeur& j, sf::Packet paquet) {
    sf::TcpSocket* client;
    if(j.getPseudo() == "IA") {
        return;
    }

    client = j.getSocket();

    ReseauGlobal::EnvoiPaquet(*client, paquet);
}

void ReseauServeur::envoiPaquetATous(sf::Packet paquet) {
    for (vector<JoueurServeur>::iterator it = joueurs.begin(); it != joueurs.end(); ++it) {
        JoueurServeur& j = *it;

        envoiPaquet(j, paquet);
    }
}

void ReseauServeur::envoiATous(string& message) {
    sf::Packet paquet;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::MessageEchoServeur);

    paquet << typePaquet << message;

    for (vector<JoueurServeur>::iterator it = joueurs.begin(); it != joueurs.end(); ++it) {
        // On récupère les infos du client dans la liste
        JoueurServeur& j = *it;

        envoiPaquet(j, paquet);
    }
}

void ReseauServeur::envoiPlateau(JoueurServeur& joueur, PlateauServeur& plateau) {
    sf::Packet paquet;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Plateau);

    paquet << typePaquet << plateau;

    envoiPaquet(joueur, paquet);
    envoiZoneVisible(joueur);
}

void ReseauServeur::envoiPlateauATous() {
    sf::Packet paquet;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Plateau);

    paquet << typePaquet << plateau;

    for (vector<JoueurServeur>::iterator it = joueurs.begin(); it != joueurs.end(); ++it) {
        // On récupère les infos du client dans la liste
        JoueurServeur& j = *it;

        envoiPaquet(j, paquet);
        envoiZoneVisible(j);
    }
}

void ReseauServeur::envoiZoneParcourable(JoueurServeur& joueur, Position pos) {
    sf::Packet paquet;
    std::list<NoeudServeur> noeuds;
    std::list<NoeudServeur>::iterator noeudIterator;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::ZoneParcourable);
    sf::Int32 tailleZone;

    if(joueur.getId() != plateau.cellule[pos.x][pos.y].getIdJoueur()) {
        return;
    }

    noeuds = plateau.getZoneParcourable(pos, joueur.getEnergie());

    tailleZone = noeuds.size();

    paquet << typePaquet << tailleZone;

    for (noeudIterator = noeuds.begin(); noeudIterator != noeuds.end(); noeudIterator++) {
        paquet << noeudIterator->getPosition();
    }

    envoiPaquet(joueur, paquet);
}

void ReseauServeur::envoiJoueurCourant(JoueurServeur& joueur) {
    sf::Packet paquet;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::JoueurCourant);

    paquet << typePaquet << joueur;

    envoiPaquet(joueur, paquet);
}

void ReseauServeur::envoiJoueursAdverses(JoueurServeur& joueur) {
    sf::Packet paquet;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::JoueursAdverses);

    paquet << typePaquet << (sf::Int32) joueurs.size() - 1;

    for (vector<JoueurServeur>::iterator j = joueurs.begin(); j != joueurs.end(); ++j) {
        if(j->getId() != joueur.getId())
            paquet << j->getPseudo();
    }

    envoiPaquet(joueur, paquet);
}

void ReseauServeur::envoiChemin(JoueurServeur& joueur, Position posDepart, Position posArrivee) {
    sf::Packet paquet;
    std::list<NoeudServeur> noeuds;
    std::list<Position>::iterator cheminIterator;
    std::list<Position> chemin;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Chemin);
    sf::Int32 tailleChemin;

    if(joueur.getId() != plateau.cellule[posDepart.x][posDepart.y].getIdJoueur()) {
        return;
    }

    noeuds = plateau.getZoneParcourable(posDepart, joueur.getEnergie());

    chemin = PlateauServeur::obtenirChemin(posArrivee, noeuds);

    tailleChemin = chemin.size();

    paquet << typePaquet << tailleChemin;

    for(cheminIterator = chemin.begin(); cheminIterator != chemin.end(); cheminIterator++) {
        paquet << *cheminIterator;
    }

    envoiPaquet(joueur, paquet);
}

void ReseauServeur::deplacerVaisseau(JoueurServeur& joueur, Position posDepart, Position posArrivee) {
    sf::Packet paquet;
    sf::Uint16 paquetDeplacerVaisseau = static_cast<sf::Uint16>(TypePaquet::DeplacerVaisseau);
    sf::Uint16 paquetDeplacementImpossible = static_cast<sf::Uint16>(TypePaquet::DeplacementVaisseauImpossible);
    std::string message;
    ostringstream p1, p2;

    if(joueur.getId() != plateau.cellule[posDepart.x][posDepart.y].getIdJoueur()) {
        return;
    }

    if(plateau.deplacerVaisseau(posDepart, posArrivee, plateau.getZoneParcourable(posDepart, joueur.getEnergie()), joueur)) {
        paquet << paquetDeplacerVaisseau;

        p1 << posArrivee.x;
        p2 << posArrivee.y;

        message = "Deplacement d'un vaisseau (" + p1.str() + "," + p2.str() + ") par le joueur " + joueur.getPseudo();
        envoiATous(message);
        envoiPlateauATous();
    } else {
        paquet << paquetDeplacementImpossible;
    }

    envoiJoueurCourant(joueur);
    envoiPaquet(joueur, paquet);
}

void ReseauServeur::attaquerVaisseau(JoueurServeur& joueur, Position posAttaquant, Position posCible) {
    sf::Packet paquet;
    sf::Uint16 paquetAttaquerVaisseau = static_cast<sf::Uint16>(TypePaquet::AttaquerVaisseau);
    sf::Uint16 paquetAttaqueImpossible = static_cast<sf::Uint16>(TypePaquet::AttaqueVaisseauImpossible);
    CelluleServeur cAttaquant, cCible;
    std::string message;
    ostringstream p1, p2;

    if(joueur.getId() != plateau.cellule[posAttaquant.x][posAttaquant.y].getIdJoueur()) {
        return;
    }

    if(joueur.getId() == plateau.cellule[posCible.x][posCible.y].getIdJoueur()) {
        return;
    }
    
    cAttaquant = plateau.cellule[posAttaquant.x][posAttaquant.y];
    cCible = plateau.cellule[posCible.x][posCible.y];

    if(plateau.attaquer(posAttaquant, posCible, joueur)) {
        paquet << paquetAttaquerVaisseau << posCible;

        p1 << posCible.x;
        p2 << posCible.y;

        message = "Attaque d'un vaisseau (" + p1.str() + "," + p2.str() + ") par le joueur " + joueur.getPseudo();
        envoiATous(message);

        envoiPlateauATous();
    } else {
        paquet << paquetAttaqueImpossible << posCible;
    }
    
    envoiJoueurCourant(joueur);
    envoiPaquet(joueur, paquet);
}

void ReseauServeur::envoiZoneConstructibleVaisseau(JoueurServeur& joueur) {
    sf::Packet paquet;
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

    envoiPaquet(joueur, paquet);
}

void ReseauServeur::envoiZoneConstructibleBatiment(JoueurServeur& joueur, Position p) {
    sf::Packet paquet;
    std::list<Position> listePos;
    std::list<Position>::iterator pos;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::ZoneConstructibleBatiment);
    sf::Int32 tailleZone;

    if(joueur.getId() != plateau.cellule[p.x][p.y].getIdJoueur()) {
        return;
    }

    listePos = plateau.getZoneConstructibleBatiment(p, joueur.getId());

    tailleZone = listePos.size();

    paquet << typePaquet << tailleZone;

    for (pos = listePos.begin(); pos != listePos.end(); pos++) {
        paquet << *pos;
    }

    envoiPaquet(joueur, paquet);
}

void ReseauServeur::envoiZoneAttaquable(JoueurServeur& joueur, Position p) {
    sf::Packet paquet;
    std::list<NoeudServeur> noeuds;
    std::list<NoeudServeur>::iterator noeudIterator;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::ZoneAttaquable);
    sf::Int32 tailleZone;

    if(joueur.getId() != plateau.cellule[p.x][p.y].getIdJoueur()) {
        return;
    }

    noeuds = plateau.getZoneAttaquable(p);

    tailleZone = noeuds.size();

    paquet << typePaquet << tailleZone;

    for (noeudIterator = noeuds.begin(); noeudIterator != noeuds.end(); noeudIterator++) {
        paquet << noeudIterator->getPosition();
    }

    envoiPaquet(joueur, paquet);
}

void ReseauServeur::envoiVaisseauxConstructibles(JoueurServeur& joueur) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::VaisseauxConstructibles);
    std::vector<VaisseauServeur> listeVaisseaux = joueur.getVaisseauxConstructibles();
    std::vector<VaisseauServeur>::iterator vaisseauIterator;
    sf::Packet paquet;
    sf::Int32 nbVaisseaux;

    nbVaisseaux = listeVaisseaux.size();

    paquet << typePaquet << nbVaisseaux;

    for (vaisseauIterator = listeVaisseaux.begin(); vaisseauIterator != listeVaisseaux.end(); vaisseauIterator++) {
        paquet << *vaisseauIterator;
    }

    envoiPaquet(joueur, paquet);
}

void ReseauServeur::envoiBatimentsConstructibles(JoueurServeur&, Position) {
    /*sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::BatimentsConstructibles);
    std::vector<VaisseauServeur> listeVaisseaux = joueur.getBatimentsConstructibles();
    std::vector<VaisseauServeur>::iterator vaisseauIterator;
    sf::Packet paquet;
    sf::Int32 nbVaisseaux;

    nbVaisseaux = listeVaisseaux.size();

    paquet << typePaquet << nbVaisseaux;

    for (vaisseauIterator = listeVaisseaux.begin(); vaisseauIterator != listeVaisseaux.end(); vaisseauIterator++) {
        paquet << *vaisseauIterator;
    }

    envoiPaquet(joueur, paquet);
    */
    // TODO
}

void ReseauServeur::envoiZoneVisible(JoueurServeur& joueur) {
    sf::Packet paquet;
    std::list<NoeudServeur> noeuds;
    std::list<NoeudServeur>::iterator noeudIterator;
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::ZoneVisible);
    sf::Int32 tailleZone;

    noeuds = plateau.getZoneVisible(joueur.getId());

    tailleZone = noeuds.size();

    paquet << typePaquet << tailleZone;

    for (noeudIterator = noeuds.begin(); noeudIterator != noeuds.end(); noeudIterator++) {
        paquet << noeudIterator->getPosition();
    }

    envoiPaquet(joueur, paquet);
}

void ReseauServeur::creerBase(JoueurServeur& joueur, int nbJoueurs) {
    sf::Int32 posX;
    sf::Int32 posY;

    if(nbJoueurs == 1) {
        posX = 2;
        posY = 2;
        
        plateau.cellule[3][3].creerVaisseau(TypeVaisseau::Destructeur);
        joueur.ajouterVaisseau(plateau.cellule[3][3].getVaisseau());
        plateau.cellule[4][3].creerVaisseau(TypeVaisseau::Constructeur);
        joueur.ajouterVaisseau(plateau.cellule[4][3].getVaisseau());
        plateau.cellule[4][4].creerVaisseau(TypeVaisseau::Croiseur);
        joueur.ajouterVaisseau(plateau.cellule[4][4].getVaisseau());
        plateau.cellule[4][1].creerBatiment(TypeBatiment::Mine);
        joueur.ajouterBatiment(plateau.cellule[4][1].getBatiment());

        plateau.cellule[plateau.getTailleX() - 7][plateau.getTailleY() - 6].creerVaisseau(TypeVaisseau::Chasseur);
        joueur.ajouterVaisseau(plateau.cellule[plateau.getTailleX() - 7][plateau.getTailleY() - 6].getVaisseau());
    }
    else {
        posX = plateau.getTailleX() - 2;
        posY = plateau.getTailleY() - 2;

        plateau.cellule[posX -  3][posY - 3].creerVaisseau(TypeVaisseau::Destructeur);
        joueur.ajouterVaisseau(plateau.cellule[posX - 3][posY - 3].getVaisseau());
        plateau.cellule[posX - 4][posY - 3].creerVaisseau(TypeVaisseau::Constructeur);
        joueur.ajouterVaisseau(plateau.cellule[posX - 4][posY - 3].getVaisseau());
        plateau.cellule[posX - 4][posY - 4].creerVaisseau(TypeVaisseau::Croiseur);
        joueur.ajouterVaisseau(plateau.cellule[posX - 4][posY - 4].getVaisseau());
        plateau.cellule[posX - 4][posY - 1].creerBatiment(TypeBatiment::Mine);
        joueur.ajouterBatiment(plateau.cellule[posX - 4][posY - 1].getBatiment());

        plateau.cellule[5][4].creerVaisseau(TypeVaisseau::Chasseur);
        joueur.ajouterVaisseau(plateau.cellule[5][4].getVaisseau());
    }

    plateau.cellule[posX][posY].creerBatiment(TypeBatiment::Base);
    joueur.ajouterBatiment(plateau.cellule[posX][posY].getBatiment());

    if((nbJoueurs > 1) && !partieSolo) {
        demarrerPartieMulti();
    }
    else if ((nbJoueurs > 1) && partieSolo) {
        demarrerPartieSolo();
    }
}

void ReseauServeur::demarrerPartieMulti() {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::DemarrerPartieMulti);
    sf::Packet paquet;

    paquet << typePaquet;

    envoiPaquetATous(paquet);

    joueurSuivant();
}

void ReseauServeur::demarrerPartieSolo() {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::DemarrerPartieSolo);
    sf::Packet paquet;

    paquet << typePaquet;

    envoiPaquetATous(paquet);

    joueurSuivant();
}

void ReseauServeur::jouerIA() {
    Position p = Position(-1, -1);

    // Ce n'est pas une partie solo, pas d'IA
    if(!partieSolo) {
        return;
    }

    // On vérifie si on a assez de commandement
    if (joueurs[1].getCommandement() < 2) {
        joueurSuivant();
        return;
    }

    // Si on n'a pas assez d'énergie, on construit une mine
    if (joueurs[1].getEnergie() < 50) {

        // On essaye de trouver un vaisseau constructeur
        p = plateau.getVaisseauConstructeur(joueurs[1].getId());
        if( p != Position(-1, -1) ) {
            std::list<Position> listePos;
            Position posConstruction;

            listePos = plateau.getZoneConstructibleBatiment(p, joueurs[1].getId());

            if (listePos.size() >= 1) {
                posConstruction = listePos.front();

                plateau.cellule[posConstruction.x][posConstruction.y].creerBatiment(TypeBatiment::Mine);
                joueurs[1].ajouterBatiment(plateau.cellule[posConstruction.x][posConstruction.y].getBatiment());
                joueurs[1].setCommandement(joueurs[1].getCommandement() - 1);

                joueurSuivant();
                return;
            }
        }
    }

    joueurSuivant();
}

void ReseauServeur::joueurSuivant() {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::JoueurSuivant);
    sf::Packet paquet;

    // La partie n'est pas encore commencée
    if(joueurActuel == -1) {
        joueurActuel = 1;
    }

    // La partie est déjà en cours
    else {
        if(joueurActuel == 1) {
            joueurActuel = 2;

            // IA
            if(partieSolo) {
                jouerIA();
            }
        }
        // Fin d'un tour
        else {
            joueurActuel = 1;

            // On redonne des ressources
            for (vector<JoueurServeur>::iterator it = joueurs.begin(); it != joueurs.end(); ++it) {
                JoueurServeur& j = *it;

                j.effectuerTour();
                plateau.effectuerTour();
                envoiJoueurCourant(j);
            }
        }
    }

    cout << "C'est au tour du joueur " << joueurActuel << " de jouer" << endl;

    paquet << typePaquet << joueurActuel;
    envoiPaquetATous(paquet);
    envoiPlateauATous();
}

void ReseauServeur::construireVaisseau(JoueurServeur& joueur, sf::Packet paquet) {
    sf::Uint16 typeVaisseau;
    TypeVaisseau type;
    Position p;

    paquet >> typeVaisseau >> p;

    type = static_cast<TypeVaisseau>(typeVaisseau);

    plateau.cellule[p.x][p.y].creerVaisseauTest(type);
    joueur.ajouterVaisseau(plateau.cellule[p.x][p.y].getVaisseau());

    envoiPlateauATous();
}

void ReseauServeur::construireBatiment(JoueurServeur& joueur, sf::Packet paquet) {
    sf::Uint16 typeBatiment = static_cast<sf::Uint16>(TypeBatiment::Inexistant);
    Position p;
    TypeBatiment type;

    paquet >> typeBatiment >> p;

    type = static_cast<TypeBatiment>(typeBatiment);

    plateau.cellule[p.x][p.y].creerBatiment(type);
    joueur.ajouterBatiment(plateau.cellule[p.x][p.y].getBatiment());

    envoiPlateauATous();
}

void ReseauServeur::ecouterReseau(void) {

    envoiHeartbeat();
    
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

                // Si on est en partie solo, on crée l'IA
                if(partieSolo) {

                    j = new JoueurServeur();
                    j->setPseudo("IA");
                    j->setSocket(NULL);
                    j->setId(joueurs.size()+1);

                    joueurs.push_back(*j);
                    creerBase(*j, joueurs.size());
                }

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
                            sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::SupprimerJoueur);
                            sf::Packet paquet;
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

                            paquet << typePaquet;
                            envoiPaquetATous(paquet);
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
    cout << "[RESEAU] Fermeture de la socket du serveur" << endl;

    actif = false;

    selector.clear();
    listener.close();
    socketMaster.disconnect();
}

void ReseauServeur::envoiHeartbeat() {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::MasterHeartbeat);
    sf::Time tempsEcoule;
    sf::Packet paquet;

    if(partieSolo) {
        return;
    }

    if(!masterActif) {
        return;
    }

    tempsEcoule = timer.getElapsedTime();

    if((tempsEcoule.asSeconds() - dernierHeartbeat.asSeconds()) < 60) {
        return;
    } 

    paquet << typePaquet << port << nom;

    dernierHeartbeat = tempsEcoule;

    cout << "[RESEAU] Envoi d'un heartbeat au Master Serveur" << endl;

    ReseauGlobal::EnvoiPaquet(socketMaster, paquet);
}

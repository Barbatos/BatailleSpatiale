#include "ReseauClient.hpp"

#include <client/utile/Notification.hpp>

ReseauClient::ReseauClient(Plateau& _plateau, Joueur& _joueur) :
        ip("none"), port(0), plateau(_plateau), joueur(_joueur), partieSolo(
                false) {
    setActif(false);
    setPartieActive(false);
    setBloquerJeu(true);

    ConnexionMasterServeur();
}

ReseauClient::~ReseauClient() {
    socket.disconnect();
    socketMaster.disconnect();
}

void ReseauClient::ConnexionServeur(string ip, unsigned short port,
        bool _partieSolo) {
    sf::IpAddress server(ip);
    sf::Time timeout = sf::seconds(1);
    int nbEssais = 0;

    if (_partieSolo) {
        partieSolo = _partieSolo;
    }

    if (getActif() == true) {
        notification.ajouterMessage(L"[RESEAU]", L"Vous êtes déjà connecté à un serveur !", 5000);
        return;
    }

    if (server == sf::IpAddress::getPublicAddress()) {
        server = sf::IpAddress("localhost");
    }

    while (getActif() == false) {
        if(socket.connect(server, port, timeout) != sf::Socket::Done) {
            socket.disconnect();

            if (nbEssais >= 5) {
                notification.ajouterMessage(L"[RESEAU]", L"Impossible de se connecter au serveur", 5000);
                cout << "[RESEAU] Abandon de la tentative de connexion au serveur " << ip 
                << endl;
                return;
            }

            cout << "Impossible de se connecter au serveur sur le port" << port << ", essai sur le port " << (port+1) << endl;

            port++;
            nbEssais++;

            continue;
        }
        setActif(true);
    }

    // On met la socket en mode non-bloquant
    socket.setBlocking(false);

    // On définit que le réseau est maintenant actif
    setActif(true);

    notification.ajouterMessage(L"[RESEAU]", L"Connecté au serveur", 5000);
}

void ReseauClient::ConnexionMasterServeur(void) {
    unsigned short portMaster = 1600;
    sf::IpAddress masterServer("barbatos.fr");
    sf::Time timeout = sf::seconds(0.2);
    int nbEssais = 0;

    while (socketMaster.connect(masterServer, portMaster, timeout)
            != sf::Socket::Done) {
        if (nbEssais >= 5) {
            notification.ajouterMessage(L"[RESEAU]", L"Abandon de la tentative de connexion au Master Serveur", 5000);
            return;
        }

        std::wstringstream stream;
        stream << L"Impossible de se connecter au serveur sur le port" << portMaster << L", essai sur le port " << (portMaster + 1);

        notification.ajouterMessage(L"[RESEAU]", stream.str(), 5000);

        portMaster++;
        nbEssais++;
    }

    socketMaster.setBlocking(false);

    notification.ajouterMessage(L"[RESEAU]", L"Connecté au Master Serveur", 5000);
}

void ReseauClient::TraiterPaquetServeur(void) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Vide);
    sf::Packet paquet;
    string message;

    if (!getActif()) {
        return;
    }

    ReseauGlobal::ReceptionPaquet(socket, paquet, sf::seconds(0.00f));

    if (paquet.getDataSize() <= 0) {
        return;
    }

    paquet >> typePaquet;

    switch (static_cast<TypePaquet>(typePaquet)) {

        case TypePaquet::Plateau:
            paquet >> plateau;
            getZoneConstructibleVaisseau();
            break;

        case TypePaquet::MessageEchoServeur:
            paquet >> message;
            notification.ajouterMessage("[RESEAU]", message, 5000);
            break;

        case TypePaquet::ZoneParcourable:
            parseZoneParcourable(paquet);
            break;

        case TypePaquet::Chemin:
            parseChemin(paquet);
            break;

        case TypePaquet::DeplacerVaisseau:
            deplacerVaisseau(paquet);
            break;

        case TypePaquet::DeplacementVaisseauImpossible:
            break;

        case TypePaquet::ZoneConstructibleVaisseau:
            parseZoneConstructibleVaisseau(paquet);
            break;

        case TypePaquet::ZoneConstructibleBatiment:
            parseZoneConstructibleBatiment(paquet);
            break;

        case TypePaquet::ZoneAttaquable:
            parseZoneAttaquable(paquet);
            break;

        case TypePaquet::JoueurCourant:
            parseJoueurCourant(paquet);
            break;

        case TypePaquet::JoueursAdverses:
            parseJoueursAdverses(paquet);
            break;

        case TypePaquet::AttaquerVaisseau:
            attaquerVaisseau(paquet);
            break;

        case TypePaquet::VaisseauxConstructibles:
            parseVaisseauxConstructibles(paquet);
            break;

        case TypePaquet::BatimentsConstructibles:
            parseBatimentsConstructibles(paquet);
            break;

        case TypePaquet::DemarrerPartieMulti:
            demarrerPartieMulti();
            break;

        case TypePaquet::DemarrerPartieSolo:
            demarrerPartieSolo();
            break;

        case TypePaquet::JoueurSuivant:
            joueurSuivant(paquet);
            break;

        case TypePaquet::ZoneVisible:
            parseZoneVisible(paquet);
            break;

        case TypePaquet::SupprimerJoueur:
            setActif(false);
            break;

        default:
            std::stringstream stream;
            stream << "Erreur : paquet de type : " << typePaquet << " inconnu";

            notification.ajouterMessage("[RESEAU]", stream.str(), 5000);
            break;
    }
}

void ReseauClient::traiterPaquetMasterServeur(void) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Vide);
    sf::Packet paquet;
    string message;

    ReseauGlobal::ReceptionPaquet(socketMaster, paquet, sf::seconds(0.00f));

    if (paquet.getDataSize() <= 0) {
        return;
    }

    paquet >> typePaquet;

    switch (static_cast<TypePaquet>(typePaquet)) {

        case TypePaquet::MasterListeServeurs:
            parseListeServeurs(paquet);
            break;

        default:
            std::stringstream stream;
            stream << "Erreur : paquet de type : " << typePaquet << " inconnu venant du Master Serveur";

            notification.ajouterMessage("[RESEAU]", stream.str(), 5000);
            break;
    }
}

void ReseauClient::demarrerPartieMulti() {
    setPartieActive(true);
}

void ReseauClient::demarrerPartieSolo() {
    setPartieActive(true);
}

void ReseauClient::joueurSuivant(sf::Packet paquet) {
    sf::Int32 numJoueur;

    paquet >> numJoueur;

    // C'est à nous de jouer
    if (joueur.getId() == numJoueur) {
        setBloquerJeu(false);
    }

    // Ce n'est pas notre tour de jouer
    else {
        setBloquerJeu(true);
    }
}

void ReseauClient::EnvoyerPseudoServeur(string pseudo) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::ChangementDeNom);
    sf::Packet paquet;

    paquet << typePaquet << pseudo;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getZoneParcourable(Position p) {
    sf::Uint16 typePaquet =
            static_cast<sf::Uint16>(TypePaquet::GetZoneParcourable);
    sf::Packet paquet;

    paquet << typePaquet << p;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::parseZoneParcourable(sf::Packet paquet) {
    sf::Int32 tailleZone;
    Position p;

    paquet >> tailleZone;

    for (sf::Int32 i = 0; i < tailleZone; i++) {
        paquet >> p;
        plateau.cellule[p.x][p.y].setParcourable(true);
    }
}

void ReseauClient::parseChemin(sf::Packet paquet) {
    sf::Int32 tailleZone;
    std::list<Position> pos;
    Position p;

    paquet >> tailleZone;

    for (sf::Int32 i = 0; i < tailleZone; i++) {
        paquet >> p;
        plateau.cellule[p.x][p.y].setEstChemin(true);
    }
}

void ReseauClient::parseZoneConstructibleVaisseau(sf::Packet paquet) {
    sf::Int32 tailleZone;
    std::list<Position> pos;
    Position p;

    paquet >> tailleZone;

    for (sf::Int32 i = 0; i < tailleZone; i++) {
        paquet >> p;
        plateau.cellule[p.x][p.y].setEstConstructibleVaisseau(true);
    }
}

void ReseauClient::parseZoneConstructibleBatiment(sf::Packet paquet) {
    sf::Int32 tailleZone;
    std::list<Position> pos;
    Position p;

    paquet >> tailleZone;

    for (sf::Int32 i = 0; i < tailleZone; i++) {
        paquet >> p;
        plateau.cellule[p.x][p.y].setEstConstructibleBatiment(true);
    }
}

void ReseauClient::parseZoneAttaquable(sf::Packet paquet) {
    sf::Int32 tailleZone;
    std::list<Position> pos;
    Position p;

    paquet >> tailleZone;

    for (sf::Int32 i = 0; i < tailleZone; i++) {
        paquet >> p;
        plateau.cellule[p.x][p.y].setEstAttaquable(true);
    }
}

void ReseauClient::parseJoueurCourant(sf::Packet paquet) {
    paquet >> joueur;
}

void ReseauClient::parseJoueursAdverses(sf::Packet paquet) {
    sf::Int32 tailleListe;
    string j;
    //vector<string> joueursAdverses;

    vector<string> joueursAdverses = joueur.getJoueursAdverses();

    paquet >> tailleListe;

    for (sf::Int32 i = 0; i < tailleListe; i++) {
        paquet >> j;
        joueursAdverses.push_back(j);
    }

    // TODO
}

void ReseauClient::parseVaisseauxConstructibles(sf::Packet paquet) {
    sf::Int32 tailleListe;
    Vaisseau v;

    paquet >> tailleListe;

    plateau.listeVaisseauxConstructibles.clear();
    plateau.listeVaisseauxConstructibles.reserve(tailleListe);

    for (sf::Int32 i = 0; i < tailleListe; i++) {
        paquet >> v;
        plateau.listeVaisseauxConstructibles.push_back(v);
    }
}

void ReseauClient::parseBatimentsConstructibles(sf::Packet paquet) {
    sf::Int32 tailleListe;
    Batiment b;

    paquet >> tailleListe;

    plateau.listeBatimentsConstructibles.clear();
    plateau.listeBatimentsConstructibles.reserve(tailleListe);

    for (sf::Int32 i = 0; i < tailleListe; i++) {
        paquet >> b;
        plateau.listeBatimentsConstructibles.push_back(b);
    }
}

void ReseauClient::parseZoneVisible(sf::Packet paquet) {
    sf::Int32 tailleZone;
    Position p;

    paquet >> tailleZone;
    
    plateau.resetZoneVisible();

    for (sf::Int32 i = 0; i < tailleZone; i++) {
        paquet >> p;
        plateau.cellule[p.x][p.y].setEstVisible(true);
    }
}

void ReseauClient::parseListeServeurs(sf::Packet paquet) {
    sf::Int32 nbServeurs;
    Serveur s;

    paquet >> nbServeurs;

    plateau.listeServeurs.clear();

    for (sf::Int32 i = 0; i < nbServeurs; i++) {
        paquet >> s;
        plateau.listeServeurs.push_back(s);
    }
}

void ReseauClient::deplacerVaisseau(sf::Packet) {
    // TODO : Messages d'erreur / validation
}

void ReseauClient::attaquerVaisseau(sf::Packet paquet) {
    Position p;

    paquet >> p;

    plateau.cellule[p.x][p.y].setEstAttaquee(true);
}

void ReseauClient::getChemin(Position depart, Position arrivee) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::GetChemin);
    sf::Packet paquet;

    paquet << typePaquet << depart << arrivee;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::demanderDeplacementVaisseau(Position depart,
        Position arrivee) {
    sf::Uint16 typePaquet =
            static_cast<sf::Uint16>(TypePaquet::DemanderDeplacementVaisseau);
    sf::Packet paquet;

    paquet << typePaquet << depart << arrivee;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getZoneConstructibleVaisseau() {
    sf::Uint16 typePaquet =
            static_cast<sf::Uint16>(TypePaquet::GetZoneConstructibleVaisseau);
    sf::Packet paquet;

    paquet << typePaquet;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getZoneConstructibleBatiment(Position p) {
    sf::Uint16 typePaquet =
            static_cast<sf::Uint16>(TypePaquet::GetZoneConstructibleBatiment);
    sf::Packet paquet;

    paquet << typePaquet << p;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getZoneAttaquable(Position p) {
    sf::Uint16 typePaquet =
            static_cast<sf::Uint16>(TypePaquet::GetZoneAttaquable);
    sf::Packet paquet;

    paquet << typePaquet << p;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getJoueurCourant() {
    sf::Uint16 typePaquet =
            static_cast<sf::Uint16>(TypePaquet::GetJoueurCourant);
    sf::Packet paquet;

    paquet << typePaquet;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getJoueursAdverses() {
    sf::Uint16 typePaquet =
            static_cast<sf::Uint16>(TypePaquet::GetJoueursAdverses);
    sf::Packet paquet;

    paquet << typePaquet;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::demanderAttaqueVaisseau(Position p1, Position p2) {
    sf::Uint16 typePaquet =
            static_cast<sf::Uint16>(TypePaquet::DemanderAttaqueVaisseau);
    sf::Packet paquet;

    paquet << typePaquet << p1 << p2;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::demanderListeServeurs() {
    sf::Uint16 typePaquet =
            static_cast<sf::Uint16>(TypePaquet::MasterGetServeurs);
    sf::Packet paquet;

    paquet << typePaquet;

    ReseauGlobal::EnvoiPaquet(socketMaster, paquet);
}

void ReseauClient::getVaisseauxConstructibles() {
    sf::Uint16 typePaquet =
            static_cast<sf::Uint16>(TypePaquet::GetVaisseauxConstructibles);
    sf::Packet paquet;

    paquet << typePaquet;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getBatimentsConstructibles(Position p) {
    sf::Uint16 typePaquet =
            static_cast<sf::Uint16>(TypePaquet::GetBatimentsConstructibles);
    sf::Packet paquet;

    paquet << typePaquet << p;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getZoneVisible() {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::GetZoneVisible);
    sf::Packet paquet;

    paquet << typePaquet;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::demanderFinTour() {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::DemanderFinTour);
    sf::Packet paquet;

    paquet << typePaquet;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::demanderConstructionVaisseau(TypeVaisseau v, Position p) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::DemanderConstructionVaisseau);
    sf::Uint16 typeVaisseau = static_cast<sf::Uint16>(v);
    sf::Packet paquet;

    paquet << typePaquet << typeVaisseau << p;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::demanderConstructionBatiment(TypeBatiment b, Position p) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::DemanderConstructionBatiment);
    sf::Uint16 typeBatiment = static_cast<sf::Uint16>(b);
    sf::Packet paquet;

    paquet << typePaquet << typeBatiment << p;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::setDestination(Position p) {
    plateau.cellule[p.x][p.y].setEstDestination(true);
}

void ReseauClient::setActif(bool _actif) {
    actif = _actif;
}

bool ReseauClient::getActif(void) {
    return actif;
}

void ReseauClient::setPartieActive(bool _active) {
    partieActive = _active;
}

bool ReseauClient::getPartieActive() {
    return partieActive;
}

bool ReseauClient::getPartieSolo() {
    return partieSolo;
}

void ReseauClient::setBloquerJeu(bool _bloquer) {
    bloquerJeu = _bloquer;
}

bool ReseauClient::getBloquerJeu() {
    return bloquerJeu;
}

void ReseauClient::setPartieSolo(bool _partieSolo) {
    partieSolo = _partieSolo;
}

void ReseauClient::setIp(string _ip) {
    ip = _ip;
}

void ReseauClient::setPort(unsigned short _port) {
    port = _port;
}

sf::TcpSocket& ReseauClient::getSocket(void) {
    return socket;
}

void ReseauClient::deconnexion() {
    cout << "[RESEAU] Deconnexion" << endl;
    setActif(false);
    socket.disconnect();
}

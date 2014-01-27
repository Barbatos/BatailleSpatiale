#include "ReseauClient.hpp"

ReseauClient::ReseauClient(Plateau& _plateau, Joueur& _joueur)
                : ip("none"), port(0), plateau(_plateau), joueur(_joueur) {
    setActif(false);
}

ReseauClient::~ReseauClient() {

}

void ReseauClient::ConnexionServeur(string ip, unsigned short port) {
    sf::IpAddress server(ip);
    sf::Time timeout = sf::seconds(2);
    int nbEssais = 0;

    if (getActif() == true) {
        cout << "[RESEAU] Vous êtes déjà connecté à un serveur !" << endl;
        return;
    }

    while(socket.connect(server, port, timeout) != sf::Socket::Done) {
        if(nbEssais >= 5) {
            cout << "[RESEAU] Abandon de la tentative de connexion au serveur" << endl;
            return;
        }

        cout << "[RESEAU] Impossible de se connecter au serveur sur le port " << port << ", essai sur le port " << (port+1) << endl;

        port++;
        nbEssais++;
    }

    // On met la socket en mode non-bloquant
    socket.setBlocking(false);

    // On définit que le réseau est maintenant actif
    setActif(true);

    cout << "[RESEAU] Connecté au serveur " << server << endl;
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
            break;

        case TypePaquet::MessageEchoServeur:
            paquet >> message;
            cout << "[SERVEUR] " << message << endl;
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

        default:
            cout << "[RESEAU] Erreur: paquet de type " << typePaquet << " inconnu" << endl;
            break;
    }
}

/// Après la connexion, on dit bonjour au serveur
/// en lui donnant notre pseudo
void ReseauClient::EnvoyerPseudoServeur(string pseudo) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::ChangementDeNom);
    sf::Packet paquet;

    paquet << typePaquet << pseudo;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getZoneParcourable(Position p) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::GetZoneParcourable);
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
    vector<string> joueursAdverses;

    paquet >> tailleListe;

    for (sf::Int32 i = 0; i < tailleListe; i++) {
        paquet >> j;
        joueursAdverses.push_back(j);
    }

    // TODO
}

void ReseauClient::deplacerVaisseau(sf::Packet) {
    // TODO : Messages d'erreur / validation
}

void ReseauClient::attaquerVaisseau(sf::Packet) {
    // TODO : Messages d'erreur / validation
}

void ReseauClient::getChemin(Position depart, Position arrivee) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::GetChemin);
    sf::Packet paquet;

    paquet << typePaquet << depart << arrivee;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::demanderDeplacementVaisseau(Position depart, Position arrivee) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::DemanderDeplacementVaisseau);
    sf::Packet paquet;

    paquet << typePaquet << depart << arrivee;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getZoneConstructibleVaisseau(Position p) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::GetZoneConstructibleVaisseau);
    sf::Packet paquet;

    paquet << typePaquet << p;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getZoneConstructibleBatiment(Position p) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::GetZoneConstructibleBatiment);
    sf::Packet paquet;

    paquet << typePaquet << p;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getZoneAttaquable(Position p) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::GetZoneAttaquable);
    sf::Packet paquet;

    paquet << typePaquet << p;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getJoueurCourant() {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::GetJoueurCourant);
    sf::Packet paquet;

    paquet << typePaquet;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::getJoueursAdverses() {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::GetJoueursAdverses);
    sf::Packet paquet;

    paquet << typePaquet;

    ReseauGlobal::EnvoiPaquet(socket, paquet);
}

void ReseauClient::demanderAttaqueVaisseau(Position p1, Position p2) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::DemanderAttaqueVaisseau);
    sf::Packet paquet;

    paquet << typePaquet << p1 << p2;

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

void ReseauClient::setIp(string _ip) {
    ip = _ip;
}

void ReseauClient::setPort(unsigned short _port) {
    port = _port;
}

sf::TcpSocket& ReseauClient::getSocket(void) {
    return socket;
}

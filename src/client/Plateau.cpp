#include "Plateau.hpp"
#include <iostream>
#include "../core/enum/TypePaquet.hpp"

extern Joueur JoueurNull;

Plateau::Plateau(std::string adresseServeur, int port) :
    gestionServeur(&Plateau::gererServeur, this),
    tourJoueur(false) {

    joueur.reset(new Joueur());
    sf::IpAddress serveur(adresseServeur);

    //si on arrive pas a se connecter on quitte
    if (socket.connect(serveur, port) != sf::Socket::Done)
        throw "Impossible de se connecter au serveur";

    sf::Socket::Status codeRetour;
    sf::Packet paquet;
    if ((codeRetour = socket.receive(paquet)) == sf::Socket::Done) {
        traiterPaquet(paquet);
    }

    gestionServeur.launch();
}

Plateau::~Plateau() {
    gestionServeur.terminate();
    socket.disconnect();
}

sf::Socket::Status Plateau::envoyerMessageServeur(std::string message) {
    sf::Packet paquet;
    paquet << static_cast<sf::Uint16>(TypePaquet::MessageEchoServeur) << message;
    return socket.send(paquet);
}

sf::Socket::Status Plateau::envoyerMessagePourTous(std::string message) {
    sf::Packet paquet;
    paquet << static_cast<sf::Uint16>(TypePaquet::MessageEcho) << message;
    return socket.send(paquet);
}

bool Plateau::possedeEvenement(Position p) {
    return cellule[p.x][p.y].possedeEvenement();
}

const DetailEvenement& Plateau::getEvenement(Position p) {
    return cellule[p.x][p.y].getEvenement();
}

bool Plateau::possedeBatiment(Position p) {
    return cellule[p.x][p.y].possedeBatiment();
}

const DetailBatiment& Plateau::getBatiment(Position p) {
    return cellule[p.x][p.y].getBatiment();
}

bool Plateau::possedeVaisseau(Position p) {
    return cellule[p.x][p.y].possedeVaisseau();
}

const DetailVaisseau& Plateau::getVaisseau(Position p) {
    return cellule[p.x][p.y].getVaisseau();
}

bool Plateau::deplacerVaisseau(Position depart, Position arrivee) {
    if(depart.x < tailleX && arrivee.x < tailleX &&
            depart.x >= 0 && arrivee.x >= 0 &&
            depart.y < tailleY && arrivee.y < tailleY &&
            depart.y >= 0 && arrivee.y >= 0) {
        cellule[arrivee.x][arrivee.y].echangerVaisseau(cellule[depart.x][depart.y]);
        return true;
    }
    return false;
}

void Plateau::renommerJoueur(std::string nouveauNom) {
    sf::Packet paquet;
    paquet << static_cast<sf::Uint16>(TypePaquet::ChangementDeNom) << nouveauNom;
    socket.send(paquet);
}

const std::string& Plateau::getNomJoueur() const {
    return joueur->getNom();
}

void Plateau::gererServeur() {
    sf::Socket::Status codeRetour;
    sf::Packet paquet;
    while(codeRetour == sf::Socket::Done) {
        if ((codeRetour = socket.receive(paquet)) == sf::Socket::Done) {
            traiterPaquet(paquet);
        }
    }
}

void Plateau::traiterPaquet(sf::Packet& paquet) {
    sf::Uint16 typePaquet = static_cast<sf::Uint16>(TypePaquet::Vide);
    while(!paquet.endOfPacket()) {
        // On traite ici le paquet
        typePaquet = static_cast<sf::Uint16>(TypePaquet::Vide);
        if(!(paquet >> typePaquet))
            std::cout << "[ERREUR] Type paquet inconnu ou malformé" << std::endl;
        switch(static_cast<TypePaquet>(typePaquet)) {
        case TypePaquet::MessageEchoServeur: {
            std::string message;
            paquet >> message;
            std::cout << "[MESSAGE SERVEUR] " << message << std::endl;
        }
        break;

        case TypePaquet::MessageEcho: {
            std::string message;
            sf::Int32 identifiant;
            paquet >> identifiant >> message;
            if(identifiant != numeroJoueur) {
                std::cout << getJoueur(identifiant).getNom() << " dit : " << message << std::endl;
            }
        }
        break;

        case TypePaquet::PING: {
            sf::Packet paquet2;
            paquet2 << static_cast<sf::Uint16>(TypePaquet::PONG);
            std::cout << "[" << socket.getRemoteAddress() << "] " << "PING" << std::endl;
            socket.send(paquet2);
        }
        break;

        case TypePaquet::Joueur: {
            Joueur *joueur = new Joueur();
            paquet >> *joueur;
            if(getJoueur(joueur->getId()) == JoueurNull)
                listeJoueur.push_back(joueur);
        }
        break;

        case TypePaquet::NumeroJoueur:
            paquet >> numeroJoueur;
            break;

        case TypePaquet::Plateau:
            paquet >> *this;
            break;

        case TypePaquet::ActualiserJoueur:
            actualiserJoueur(paquet);
            break;

        case TypePaquet::SupprimerJoueur:
            supprimerJoueur(paquet);
            break;

        default:
            std::cout << "[ERREUR] Paquet de type : " << typePaquet
                      << " non géré par le client" << std::endl;
            paquet.clear();
            break;
        }
    }
}

void Plateau::actualiserJoueur(sf::Packet& paquet) {
    sf::Int32 id = -1;
    paquet >> id;

    for(Joueur* joueur : listeJoueur) {
        if(joueur->getId() == id) {
            paquet >> *joueur;
            return;
        }
    }
}

void Plateau::supprimerJoueur(sf::Packet& paquet) {
    sf::Int32 id = -1;
    paquet >> id;

    for(std::list<Joueur*>::iterator joueur(listeJoueur.begin());
            joueur != listeJoueur.end(); ++joueur) {
        if((*joueur)->getId() == id) {
            listeJoueur.erase(joueur);
            return;
        }
    }
}

sf::Packet& operator >>(sf::Packet& paquet, Plateau& plateau) {

    sf::Int16 nbJoueurs;
    Joueur *joueur;

    paquet >> plateau.tailleX >> plateau.tailleY;

    plateau.cellule.resize(plateau.tailleX, std::vector<Cellule>(plateau.tailleY));

    for (sf::Int32 x = 0 ; x < plateau.tailleX ; ++x)
        for (sf::Int32 y = 0 ; y < plateau.tailleY ; ++y)
            paquet >> plateau.cellule[x][y];

    paquet >> nbJoueurs;

    plateau.listeJoueur.clear();
    for(sf::Int16 i = 0; i < nbJoueurs; ++i) {
        joueur = new Joueur();
        paquet >> *joueur;
        if(joueur->getId() == plateau.numeroJoueur)
            plateau.joueur.reset(joueur);
        plateau.listeJoueur.push_back(joueur);
    }

    return paquet;
}

const std::list<Joueur*>& Plateau::getJoueurs() {
    return listeJoueur;
}

const Joueur& Plateau::getJoueur(sf::Int16 id) {
    for(Joueur* joueurCherche : listeJoueur) {
        if(joueurCherche->getId() == id)
            return *joueurCherche;
    }
    return JoueurNull;
}

bool operator==(const Joueur& j1, const Joueur& j2) {
    return j1.id == j2.id;
}

const sf::Int32& Plateau::getTailleX() const {
    return tailleX;
}

const sf::Int32& Plateau::getTailleY() const {
    return tailleY;
}

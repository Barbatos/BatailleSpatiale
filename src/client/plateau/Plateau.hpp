#ifndef PLATEAU_CLIENT_HPP
#define PLATEAU_CLIENT_HPP
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <list>
#include <string>
#include "Cellule.hpp"
#include "../Position.hpp"
#include "../Joueur.hpp"

/**
 * \brief Le plateau coté client
 *
 * Cette classe est l'unique classe que le client peut utiliser pour
 * intéragir avec le moteur.
 *
 */
class Plateau {

public:
    /**
     * \brief Constructeur par défaut il créé la connexion avec le serveur
     * C'est dans cette méthode que le plateau sera téléchargé
     *
     * \param adresseServeur L'adresse ip du serveur
     */
    Plateau(std::string adresseServeur = "127.0.0.1", int port = 50001);
    ~Plateau();
    bool possedeEvenement(Position p);
    const DetailEvenement& getEvenement(Position p);
    bool possedeBatiment(Position p);
    const DetailBatiment& getBatiment(Position p);
    bool possedeVaisseau(Position p);
    const DetailVaisseau& getVaisseau(Position p);
    bool deplacerVaisseau(Position depart, Position arrivee);
    sf::Socket::Status envoyerMessageServeur(std::string message);
    sf::Socket::Status envoyerMessagePourTous(std::string message);
    const std::string& getNomJoueur() const;
    const std::list<Joueur*>& getJoueurs();
    void renommerJoueur(std::string nouveauNom);

private:
    /**
     * \brief recupere le joueur qui possede cet id
     * 
     * \param id l'id du joueur
     */
    const Joueur& getJoueur(sf::Int16 id);
    void gererServeur();
    void traiterPaquet(sf::Packet& paquet);
    void actualiserJoueur(sf::Packet& paquet);
    void supprimerJoueur(sf::Packet& paquet);
    /// Les cellules du plateau
    std::vector<std::vector<Cellule>> cellule;
    sf::Int32 tailleX;///< Taille du plateau en X
    sf::Int32 tailleY;///< Taille du plateau en Y
    sf::Int32 numeroJoueur;///< Le numero du joueur sur ce client
    std::shared_ptr<Joueur> joueur;///< Le joueur sur ce client
    /// La liste des joueurs présents
    std::list<Joueur*> listeJoueur;
    /// La socket pour interagir avec le serveur
    sf::TcpSocket socket;
    /// Le thread de gestion des paquets du serveur
    sf::Thread gestionServeur;
    /// Booléen pour savoir si c'est au tour du joueur de jouer
    bool tourJoueur;

    friend sf::Packet& operator >>(sf::Packet& paquet, Plateau& plateau);
};

bool operator==(const Joueur& j1, const Joueur& j2);

sf::Packet& operator >>(sf::Packet& paquet, Plateau& plateau);

#endif /* PLATEAU_CLIENT_HPP */

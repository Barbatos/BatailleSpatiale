#ifndef PLATEAU_CLIENT_HPP
#define PLATEAU_CLIENT_HPP
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <list>
#include <string>
#include "plateau/Cellule.hpp"
#include "Position.hpp"
#include "Joueur.hpp"

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
    Plateau();
    ~Plateau();
    bool possedeEvenement(Position p);
    const DetailEvenement& getEvenement(Position p);
    bool possedeBatiment(Position p);
    const DetailBatiment& getBatiment(Position p);
    bool possedeVaisseau(Position p);
    const DetailVaisseau& getVaisseau(Position p);
    const sf::Int16& getTailleX() const;
    const sf::Int16& getTailleY() const;

private:
    /// Les cellules du plateau
    std::vector<std::vector<Cellule>> cellule;
    sf::Int16 tailleX;///< Taille du plateau en X
    sf::Int16 tailleY;///< Taille du plateau en Y

    friend sf::Packet& operator >>(sf::Packet& paquet, Plateau& plateau);
};

sf::Packet& operator >>(sf::Packet& paquet, Plateau& plateau);

#endif /* PLATEAU_CLIENT_HPP */

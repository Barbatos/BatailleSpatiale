#ifndef JOUEUR_HPP
#define JOUEUR_HPP
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class Joueur {
public:
    Joueur(sf::Int32 _id = -1, std::string _nom = "Spectateur", sf::Int32 _energie = 0, sf::Int32 _materiaux = 0);
    const std::string& getNom() const;
    const sf::Int32& getId() const;
    
private:
    sf::Int32 id;
    std::string nom;
    sf::Int32 energie;
    sf::Int32 materiaux;
    friend sf::Packet& operator >>(sf::Packet& paquet, Joueur& joueur);

    friend bool operator==(const Joueur& j1, const Joueur& j2);
};

static Joueur JoueurNull(-2);

sf::Packet& operator >>(sf::Packet& paquet, Joueur& joueur);

#endif // JOUEUR_HPP

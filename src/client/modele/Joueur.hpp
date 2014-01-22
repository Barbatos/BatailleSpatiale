#ifndef _JOUEUR_HPP_
#define _JOUEUR_HPP_

#include <global.hpp>

/**
 * Classe permettant de stocker les informations des joueurs
 * qui sont envoyées par le serveur.
 */
class Joueur {

public:
    /**
     * \brief Constructeur par défaut
     *
     * \param _pseudo le pseudo du joueur
     * \param _commandement
     * \param _requisition
     * \param _energie
     * \param _materiaux
     */
    Joueur(string _pseudo = "Anonymous", sf::Int32 _commandement = 0,
           sf::Int32 _requisition = 0, sf::Int32 _energie = 0,
           sf::Int32 _materiaux = 0);

    /**
     * \brief Récupération du pseudo du joueur
     *
     * \return le pseudo sous forme de chaîne de caractères
     */
    string getPseudo(void);

    sf::Int32 getCommandement(void);
    sf::Int32 getRequisition(void);
    sf::Int32 getEnergie(void);
    sf::Int32 getMateriaux(void);

private:
    void setPseudo(string _pseudo);

    /// Le pseudo du joueur
    string pseudo;

    sf::Int32 commandement;

    sf::Int32 requisition;

    sf::Int32 energie;

    sf::Int32 materiaux;

    friend sf::Packet& operator >>(sf::Packet& paquet, Joueur& joueur);
    friend class ReseauClient;
};

sf::Packet& operator >>(sf::Packet& paquet, Joueur& joueur);

#endif

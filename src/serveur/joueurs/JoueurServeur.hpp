#ifndef _JOUEURSERVEUR_HPP_
#define _JOUEURSERVEUR_HPP_
#include "../structures/TechnologieStructure.hpp"
#include "../structures/batiments/TechnologieBatiment.hpp"
#include "../structures/batiments/BatimentServeur.hpp"
#include "../structures/batiments/TechnologieBatiment.hpp"
#include "../structures/vaisseaux/VaisseauServeur.hpp"

#include "../../global.hpp"

/**
 * Classe permettant de gérer les joueurs.
 */
class JoueurServeur {
public:
    /**
     * \brief Constructeur par défaut
     *
     */
    JoueurServeur(void);

    /**
     * \brief Récupération de la socket réseau du joueur
     *
     * \return un pointeur vers la socket de type sf::TcpSocket
     */
    sf::TcpSocket* getSocket(void);

    /**
     * \brief Récupération du pseudo du joueur
     *
     * \return le pseudo sous forme de chaîne de caractères
     */
    string getPseudo(void);

    /**
     * \brief Récupération de l'adresse IP du joueur
     *
     * \return l'adresse ip sous forme de chaîne de caractères
     */
    string getIp(void);

    /**
     * \brief Récupération du numéro du joueur sur le serveur
     *
     * \return Le numéro du joueur
     */
    sf::Uint16 getId(void);

    /**
     * \brief Recuperation des points de commandements du joueur
     *
     * \return Les points de commandements du joueur
     */
    sf::Int16 getCommandement(void);

    /**
     * \brief Recuperation des points de réquisitions du joueur
     *
     * \return Les points de réquisitions du joueur
     */
    sf::Int16 getRequisition(void);

    /**
     * \brief Recuperation de l'énergie du joueur
     *
     * \return L'énergie du joueur
     */
    sf::Int32 getEnergie(void);

    /**
     * \brief Recuperation des materiaux du joueur
     *
     * \return Les materiaux du joueur
     */
    sf::Int32 getMateriaux(void);

    /**
     * \brief Ajoute un vaisseau au joueur
     *
     * \param vaisseau Le vaisseau a ajouter
     */
    void ajouterVaisseau(VaisseauServeurPtr vaisseau);

    /**
     * \brief Ajoute un batiment au joueur
     *
     * \param batiment Le batiment a ajouter
     */
    void ajouterBatiment(BatimentServeurPtr batiment);

    /**
     * \brief Retire les pointeurs des vaisseaux et batiments inutiles
     *
     */
    void ajournerListeStructures();

    /// Setters
    void setSocket(sf::TcpSocket* _socket);
    void setPseudo(string _pseudo);
    void setIp(string _ip);
    void setId(sf::Uint16 _id);
    void setCommandement(sf::Int16 _commandement);
    void setRequisition(sf::Int16 _requisition);
    void setEnergie(sf::Int32 _energie);
    void setMateriaux(sf::Int32 _materiaux);
protected:

private:
    /// La technologie du joueur pour les structures
    TechnologieStructure techS;

    /// La technologie du joueur pour les vaisseaux
    TechnologieVaisseau techV;

    /// La technologie du joueur pour les batiments
    TechnologieBatiment techB;

    /// La liste des batiments du joueurs
    std::list<std::weak_ptr<BatimentServeur>> listeBatiments;

    /// La liste des vaisseaux du joueurs
    std::list<std::weak_ptr<VaisseauServeur>> listeVaisseaux;

    /// La socket du joueur
    sf::TcpSocket* socket;

    /// Le pseudo du joueur
    string pseudo;

    /// L'adresse IP du joueur
    string ip;

    /// L'identifiant (nombre positif) du joueur sur le serveur
    sf::Uint16 id;

    sf::Int16 commandement;

    sf::Int16 requisition;

    sf::Int32 energie;

    sf::Int32 materiaux;
};

#endif

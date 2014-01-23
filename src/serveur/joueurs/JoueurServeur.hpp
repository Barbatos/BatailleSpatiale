#ifndef _JOUEURSERVEUR_HPP_
#define _JOUEURSERVEUR_HPP_
#include "../structures/TechnologieStructure.hpp"
#include "../structures/batiments/TechnologieBatiment.hpp"
#include "../structures/batiments/BatimentServeur.hpp"
#include "../structures/batiments/TechnologieBatiment.hpp"
#include "../structures/vaisseaux/VaisseauServeur.hpp"
#include "../../commun/utile/Position.hpp"

#include "../../global.hpp"

/**
 * \brief Classe permettant de g�rer les joueurs.
 */
class JoueurServeur {
public:
    /**
     * \brief Constructeur par d�faut
     *
     */
    JoueurServeur(void);

    /**
     * \brief R�cup�ration de la socket r�seau du joueur
     *
     * \return un pointeur vers la socket de type sf::TcpSocket
     */
    sf::TcpSocket* getSocket(void);

    /**
     * \brief R�cup�ration du pseudo du joueur
     *
     * \return le pseudo sous forme de cha�ne de caract�res
     */
    string getPseudo(void);

    /**
     * \brief R�cup�ration de l'adresse IP du joueur
     *
     * \return l'adresse ip sous forme de cha�ne de caract�res
     */
    string getIp(void);

    /**
     * \brief R�cup�ration du num�ro du joueur sur le serveur
     *
     * \return Le num�ro du joueur
     */
    sf::Uint16 getId(void);

    /**
     * \brief Recuperation des points de commandements du joueur
     *
     * \return Les points de commandements du joueur
     */
    sf::Int32 getCommandement(void);

    /**
     * \brief Recuperation des points de r�quisitions du joueur
     *
     * \return Les points de r�quisitions du joueur
     */
    sf::Int32 getRequisition(void);

    /**
     * \brief Recuperation de l'�nergie du joueur
     *
     * \return L'�nergie du joueur
     */
    sf::Int32 getEnergie(void);

    /**
     * \brief Recuperation des materiaux du joueur
     *
     * \return Les materiaux du joueur
     */
    sf::Int32 getMateriaux(void);


    VaisseauServeur getConstructionVaisseau(int index);


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


    void ajouterConstructionVaisseau(VaisseauServeur vaisseau);


    void retirerConstructionVaisseau();


    /**
     * \brief Retire les pointeurs des vaisseaux et batiments inutiles
     *
     */
    void ajournerListeStructures();

    /**
     * \brief Ajoute ou modifie le socket du joueur
     *
     * \param _socket le nouveau socket
     */
    void setSocket(sf::TcpSocket* _socket);

    /**
     * \brief Ajoute ou modifie le pseudo du joueur
     *
     * \param _pseudo le nouveau pseudo
     */
    void setPseudo(string _pseudo);
    /**
     * \brief Ajoute ou modifie l'ip du joueur
     *
     * \param _ip la nouvelle ip
     */
    void setIp(string _ip);
    /**
     * \brief Ajoute ou modifie l'id du joueur
     *
     * \param _id le nouvel id
     */
    void setId(sf::Uint16 _id);

    /**
     * \brief Modifie le nombre de points de commandement du joueur
     *
     * \param _commandement le nombre de points de commandement
     */
    void setCommandement(sf::Int32 _commandement);

    /**
     * \brief Modifie le nombre de points de r�quisition du joueur
     *
     * \param _requisition le nombre de points de r�quisition
     */
    void setRequisition(sf::Int32 _requisition);

    /**
     * \brief Modifie le nombre de points d'�nergie du joueur
     *
     * \param _energie le nombre de points d'�nergie
     */
    void setEnergie(sf::Int32 _energie);

    /**
     * \brief Modifie le nombre de materiaux du joueur
     *
     * \param _materiaux le nombre de materiaux
     */
    void setMateriaux(sf::Int32 _materiaux);



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

    std::vector<VaisseauServeur> listeConstructionVaisseau;

    /// La socket du joueur
    sf::TcpSocket* socket;

    /// Le pseudo du joueur
    string pseudo;

    /// L'adresse IP du joueur
    string ip;

    /// L'identifiant (nombre positif) du joueur sur le serveur
    sf::Uint16 id;

    /// Les points de commandements du joueur
    sf::Int32 commandement;

    /// Les points de r�quisition du joueur
    sf::Int32 requisition;

    /// Les points d'�nergie du joueur
    sf::Int32 energie;

    /// Les materiaux du joueur
    sf::Int32 materiaux;

    friend sf::Packet& operator <<(sf::Packet& paquet, const JoueurServeur& joueur);
};

sf::Packet& operator <<(sf::Packet& paquet, const JoueurServeur& joueur);



#endif

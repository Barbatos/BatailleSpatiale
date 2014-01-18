#ifndef EVENEMENTSERVEUR_HPP
#define EVENEMENTSERVEUR_HPP
#include <SFML/System.hpp>
#include "../../../commun/enum/TypeEvenement.hpp"
#include "../../structures/batiments/BatimentServeur.hpp"
#include "../../structures/vaisseaux/VaisseauServeur.hpp"

/**
 * \brief Représente un évènement sur le serveur
 * Elle permet d'affecter les vaisseaux
 * selon certains paramêtres
 */
class EvenementServeur {

public:
    /**
     * \brief Constructeur par défaut
     *
     * \param typeEvenement Le type de l'évenement
     * \param destructible est il destructible?
     * \param _coutDeplacement si on passe par cette case combien cela coute t'il (1 normal) 2 plus difficile ...
     * \param _multiplicateurDommage Le multiplicateur de dommage si un vaisseau attaque depuis cette case
     * \param _multiplicateurDegat Le multiplicateur de degats si une structure se prend une attaque ici
     *
     */
    EvenementServeur(TypeEvenement typeEvenement, bool destructible = false,
                     sf::Int32 _coutDeplacement = 1, sf::Int32 _multiplicateurDommage = 1,
                     sf::Int32 _multiplicateurDegat = 1);

    /**
     * \brief Le destructeur
     */
    virtual ~EvenementServeur();

    /**
     * \brief activer l'evenement sur le batiment
     */
    virtual void activer(BatimentServeur*) {
    }

    /**
     * \brief desactiver l'evenement sur le batiment
     */
    virtual void desactiver(BatimentServeur*) {
    }

    /**
     * \brief activer l'evenement sur le vaisseau
     */
    virtual void activer(VaisseauServeur*) {
    }

    /**
     * \brief desactiver l'evenement sur le vaisseau
     */
    virtual void desactiver(VaisseauServeur*) {
    }

    /**
     * \brief Retourne le type d'évenement
     *
     * \return Le type d'évenement
     */
    TypeEvenement quelType();

    /**
     * \brief retourne si l'evenement est accessible
     *
     * \return vrai si l'evenement est accessible
     */
    bool estDestructible();

    /**
     * \brief retourne si l'evenement est destructible
     *
     * \return vrai si l'evenement est destructible
     */
    bool estAccessible();

    /**
     * \brief retourne si l'evenement laisse tirer
     *
     * \return vrai si l'evenement laisse tirer
     */
    bool tirPossible();

    /**
     * \brief retourne si l'evenement laisse un tir arriver ici
     *
     * \return vrai si l'evenement laisse un tir arriver ici
     */
    bool ciblePossible();

    /**
     * \brief Getter coutDeplacement
     *
     * \return le coutDeplacement
     */
    sf::Int32 getCoutDeplacement();

    /**
     * \brief Getter multiplicateurDommage
     *
     * \return le multiplicateurDommage
     */
    sf::Int32 getMultiplicateurDommage();

    /**
     * \brief Getter multiplicateurDegat
     *
     * \return le multiplicateurDegat
     */
    sf::Int32 getMultiplicateurDegat();

private:
    /// Nature de l'évènement.
    TypeEvenement type;
    /// L'évenement est destructible, on remonte une structure qui prend sa place.
    bool destructible;
    /// Nombre de deplacement a utiliser pour passer par cette case 1 par défaut -1 pour impossible
    sf::Int32 coutDeplacement;
    /// Paramètre à prendre en compte lors du calcul des dommages infligés par la structure présente.
    sf::Int32 multiplicateurDommage;
    /// Paramètre à prendre en compte lors du calcul des dommages subits par la structure présente.
    sf::Int32 multiplicateurDegat;
    
    friend sf::Packet& operator <<(sf::Packet& paquet, const EvenementServeur& evenement);
};

/**
 * \brief Permet d'empaqueter un evenement
 *
 * \param paquet Le paquet a modifier
 * \param evenement L'evenement a empaqueter
 * \return le nouveau paquet
 */
sf::Packet& operator <<(sf::Packet& paquet, const EvenementServeur& evenement);

/// Défini un std::shared_ptr vers l'evenement
typedef std::shared_ptr<EvenementServeur> EvenementServeurPtr;

const EvenementServeur EvenementNuageGaz = EvenementServeur(TypeEvenement::NuageGaz, false, 1, 2, 1);

const EvenementServeur EvenementChampMeteor = EvenementServeur(TypeEvenement::ChampMeteor, true, -1, 1, 1);

const EvenementServeur EvenementEpave = EvenementServeur(TypeEvenement::Epave, true, -1, 1, 1);

const EvenementServeur EvenementInfluenceTrouNoir = EvenementServeur(TypeEvenement::InfluenceTrouNoir, false, 3, 2, 2);

const EvenementServeur EvenementStationSpatialeAbandonnee = EvenementServeur(TypeEvenement::StationSpatialeAbandonnee, true, -1, 1, 1);

#endif // EVENEMENTSERVEUR_HPP

#ifndef EVENEMENTSERVEUR_HPP
#define EVENEMENTSERVEUR_HPP
#include <iostream>
#include <memory>
#include <SFML/System.hpp>
#include "../../../commun/enum/TypeEvenement.hpp"
#include "../../structures/batiments/BatimentServeur.hpp"
#include "../../structures/vaisseaux/VaisseauServeur.hpp"

/*
 * Classe qui permet d'affecter les vaisseaux
 * selon certains paramêtres
 */
class EvenementServeur {

    public:
        EvenementServeur(TypeEvenement typeEvenement, bool destructible = false,
            sf::Int32 _coutDeplacement = 1, sf::Int32 _multiplicateurDommage = 1,
            sf::Int32 _multiplicateurDegat = 1);
        virtual ~EvenementServeur();
        //Setters
        virtual void activer(BatimentServeur*) {
        }
        virtual void desactiver(BatimentServeur*) {
        }
        virtual void activer(VaisseauServeur*) {
        }
        virtual void desactiver(VaisseauServeur*) {
        }
        TypeEvenement quelType();
        //Getters
        bool estDestructible();
        bool estAccessible();
        bool tirPossible();
        bool ciblePossible();
        sf::Int32 getCoutDeplacement();
        sf::Int32 getMultiplicateurDommage();
        sf::Int32 getMultiplicateurDegat();

    private:
        // Nature de l'évènements.
        TypeEvenement type;
        // l'évenement est destructible, on remonte une structure qui prend sa place.
        bool destructible;
        // nombre de deplacement a utiliser pour passer par cette case 1 par défaut -1 pour impossible
        sf::Int32 coutDeplacement;
        // paramètre à prendre en compte lors du calcul des dommages infligés par la structure présente.
        sf::Int32 multiplicateurDommage;
        // paramètre à prendre en compte lors du calcul des dommages subits par la structure présente.
        sf::Int32 multiplicateurDegat;

        friend sf::Packet& operator <<(sf::Packet& paquet, const EvenementServeur& evenement);
};

sf::Packet& operator <<(sf::Packet& paquet, const EvenementServeur& evenement);

typedef std::shared_ptr<EvenementServeur> EvenementServeurPtr;

const EvenementServeur EvenementNuageGaz = EvenementServeur(TypeEvenement::NuageGaz, false, 1, 2, 1);

const EvenementServeur EvenementChampMeteor = EvenementServeur(TypeEvenement::ChampMeteor, true, -1, 1, 1);

const EvenementServeur EvenementEpave = EvenementServeur(TypeEvenement::Epave, true, -1, 1, 1);

const EvenementServeur EvenementInfluenceTrouNoir = EvenementServeur(TypeEvenement::InfluenceTrouNoir, false, 3, 2, 2);

const EvenementServeur EvenementStationSpatialeAbandonnee = EvenementServeur(TypeEvenement::StationSpatialeAbandonnee, true, -1, 1, 1);

#endif // EVENEMENTSERVEUR_HPP

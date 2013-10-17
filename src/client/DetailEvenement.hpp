#ifndef DETAIL_EVENEMENT_HPP
#define DETAIL_EVENEMENT_HPP

/**
 * \brief Défini les différents types de l'évènement
 * 
 */
class TypeEvenement{
public:
    enum type {
        Inexistant,
        ChampMeteor,
        Epave,
        InfluenceTrouNoir,
        NuageGaz,
        StationSpatialeAbandonnee,
        Nombre
    };
};

/**
 * \brief Défini les différents attributs de l'évènement
 * 
 */
struct DetailEvenement {
    TypeEvenement::type type;///< Le type de l'évènement
};

#endif

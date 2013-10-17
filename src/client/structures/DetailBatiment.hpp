#ifndef DETAIL_BATIMENT_HPP
#define DETAIL_BATIMENT_HPP

/**
 * \brief Défini les différents types de batiment
 * 
 */
class TypeBatiment{
public:
    enum type {
        Inexistant,
        Base,
        Nombre
    };
};

/**
 * \brief Défini les différents attributs du batiment
 * 
 */
struct DetailBatiment {
    TypeBatiment::type type;///< Le type du batiment
    unsigned int niveau;///< Le niveau du batiment
    unsigned int vie;///< La vie courante
    unsigned int vieMax;///< La vie maximum
    unsigned int bouclier;///< Le bouclier courant
    unsigned int bouclierMax;///< Le bouclier maximum
    float bouclierTaux;///< Le taux de dégats pris par le bouclier
    unsigned int rayonVisibilite;///< Le rayon de visibilité
    unsigned int rayonAttaque;///< Le rayon d'attaque
};

#endif

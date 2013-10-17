#ifndef DETAIL_VAISSEAU_HPP
#define DETAIL_VAISSEAU_HPP

/**
 * \brief Défini les différents types de vaisseau
 * 
 */
class TypeVaisseau {
public:
    enum type {
        Inexistant,
        Simple,
        Constructeur,
        Nombre
    };
};

/**
 * \brief Défini les différents attributs du vaisseau
 * 
 */
struct DetailVaisseau {
    TypeVaisseau::type type;///< Le type du vaisseau
    unsigned int vie;///< La vie courante
    unsigned int vieMax;///< La vie maximum
    unsigned int bouclier;///< Le bouclier courant
    unsigned int bouclierMax;///< Le bouclier maximum
    float bouclierTaux;///< Le taux de dégats pris par le bouclier
    unsigned int rayonVisibilite;///< Le rayon de visibilité
    unsigned int rayonAttaque;///< Le rayon d'attaque
    unsigned int deplacementMax;///< Le déplacement max pour un tour
};

#endif

#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP
#include "TechnologieStructure.hpp"
#include <memory>
#include <SFML/System.hpp>

/*
 * Classe qui définit les differents attributs
 * que possèdent les batiments et les vaisseaux.
 * Les classes Vaisseau et Batiment en héritent
 */

class Structure {

public:

    /**
     * \brief Constructeur par défaut de la structure
     * 
     */
    Structure(sf::Int32 _vieMax = 100, sf::Int32 _bouclierMax = 0, double _bouclierTaux = 0, sf::Int32 _visibilite = 0, sf::Int32 _attaque = 10, sf::Int32 rayonAttaque = 0, sf::Int32 _prixEnergie = 0, sf::Int32 _prixMateriaux = 0);

    /**
     * \brief Getter vie
     * Retourne la vie de la structure
     * 
     * \return la vie de la structure
     */
    sf::Int32 getVie() const;
    
    /**
     * \brief Getter vieMax
     * Retourne la vie max de la structure
     * 
     * \return la vie max de la structure
     */
    sf::Int32 getVieMax() const;
    
    /**
     * \brief Getter bouclier
     * Retourne le bouclier de la structure
     * 
     * \return le bouclier de la structure
     */
    sf::Int32 getBouclier() const;
    
    /**
     * \brief Getter bouclierMax
     * Retourne le bouclier max de la structure
     * 
     * \return le bouclier max de la structure
     */
    sf::Int32 getBouclierMax() const;
    
    /**
     * \brief Getter bouclierTaux
     * Retourne le taux que le bouclier de la structure prend en degats
     * 
     * \return le taux du bouclier
     */
    double getBouclierTaux() const;
    
    /**
     * \brief Getter visibilite
     * Retourne la visibilité de la structure
     * 
     * \return la visibilité de la structure
     */
    sf::Int32 getVisibilite() const;
    
    /**
     * \brief Getter attaque
     * Retourne l'attaque de la structure
     * 
     * \return l'attaque de la structure
     */
    sf::Int32 getAttaque() const;
    
    /**
     * \brief Retourne le prix en materiaux de la structure
     * C'est le cout qu'il faut pour construire cette unité
     * 
     * \return le prix en materiaux de la structure
     */
    sf::Int32 getPrixMateriaux() const;
    
    /**
     * \brief Retourne le prix en energie de la structure
     * C'est le cout qu'il faut pour construire cette unité
     * 
     * \return le prix en energie de la structure
     */
    sf::Int32 getPrixEnergie() const;
    
    /**
     * \brief Retourne le rayon d'attaque de la structure
     * Cette unité peut attaquer tant qu'il y a un vaisseau adverse
     * dans son rayon
     * 
     * \return le rayon d'attaque
     */
    sf::Int32 getRayonAttaque() const;
    
    /**
     * \brief Retourne l'id du joueur qui possede la structure
     * 
     * \return l'id du joueur
     */
    sf::Int32 getIdJoueur();
    
    /**
     * \brief Setter idJoueur
     * Modifie l'id du joueur de la structure
     * 
     * \param _idJoueur l'id du joueur
     */
    void setIdJoueur( sf::Int32 _idJoueur);

    /**
     * \brief Setter vie
     * Modifie la vie de la structure
     * 
     * \param _vie la nouvelle vie de la structure
     */
    void setVie( sf::Int32 const _vie);

    /**
     * \brief Setter bouclier
     * Modifie le bouclier de la structure
     * 
     * \param _bouclier le nouveau bouclier de la structure
     */
    sf::Int32  setBouclier(sf::Int32 const _bouclier);

    /**
     * \brief Setter vieMax
     * Modifie la vie max de la structure
     * 
     * \param _vieMax la vie max de la structure
     */
    void setVieMax( sf::Int32 const _vieMax);

    /**
     * \brief Setter bouclierMax
     * Modifie le bouclier max de la structure
     * 
     * \param _bouclierMax le nouveau bouclier max de la structure
     */
    void setBouclierMax( sf::Int32 const _bouclierMax);

    /**
     * \brief Setter bouclierTaux
     * Modifie le taux du bouclier de la structure
     * 
     * \param _bouclierTaux le nouveau taux bouclier de la structure
     */
    void setBouclierTaux(double const _bouclierTaux);

    /**
     * \brief Setter visibilite
     * Modifie la visibilite de la structure
     * 
     * \param _visibilite la nouvelle visibilite de la structure
     */
    void setVisibilite( sf::Int32 const _visibilite);

    /**
     * \brief Setter attaque
     * Modifie l'attaque de la structure
     * 
     * \param _attaque la nouvelle attaque de la structure
     */
    void setAttaque( sf::Int32 const _attaque);

    /**
     * \brief Setter prixMateriaux
     * Modifie le prix en materiaux de la structure
     * 
     * \param _prix le nouveau prix de la structure
     */
    void setPrixMateriaux( sf::Int32 const _prix);

    /**
     * \brief Setter prixEnergie
     * Modifie le prix en energie de la structure
     * 
     * \param _prix le nouveau prix de la structure
     */
    void setPrixEnergie( sf::Int32 const _prix);

    /**
     * \brief Setter rayonAttaque
     * Modifie le rayon d'attaque de la structure
     * 
     * \param _rayonAttaque le nouveau rayon d'attaque de la structure
     */
    void setRayonAttaque( sf::Int32 const _rayonAttaque);

    /**
     * \brief Fait subir a une structure l'attaque d'une autre
     * 
     * \param attaquant La structure attaquante
     */
    void subir(Structure const& attaquant);

    /**
     * \brief Attaque une structure
     * 
     * \param  cible La structure ciblé
     */
    void attaquer(Structure& cible) const;

    /**
     * \brief Modifie la vie de la structure d'une certaine valeur
     * valeur peut etre positif ou negatif
     * 
     * \param valeur la vie en plus ou en moins de la structure
     */
    void modifierVie(sf::Int32 const valeur);
    
    /**
     * \brief Permet de cloner une structure grace a une autre en prenant 
     * une technologie en parametre
     * 
     * \param modele la structure a copier
     * \param techS la technologie de la structure associé
     */
    static Structure cloner(Structure const& modele, TechnologieStructure techS);


protected:
    sf::Int32 vie;
    sf::Int32 vieMax;
    sf::Int32 bouclier;
    sf::Int32 bouclierMax;
    double bouclierTaux;
    sf::Int32 visibilite;
    sf::Int32 attaque;
    sf::Int32 rayonAttaque;
    sf::Int32 prixEnergie;
    sf::Int32 prixMateriaux;
    sf::Int32 idJoueur;

private:
    friend std::ostream& operator<< (std::ostream& fluxSortant, Structure const& Structure);

};

typedef std::shared_ptr<Structure> StructurePtr;

#endif // STRUCTURE_HPP

#ifndef CELLULE_HPP
#define CELLULE_HPP
#include "Evenement.hpp"
#include "structures/Batiment.hpp"
#include "structures/Vaisseau.hpp"

/**
 * \brief Défini les différents types de la cellule
 * 
 * Défini si la cellule est une cellule classique ou si elle produit de
 * l'énergie, du minerais, ...
 * 
 */
enum TypeCellule{
    CelluleVide,
    CelluleMinerais,
    CelluleEnergie,
    CelluleNbrTotal
};

/**
 * \brief Défini une case du plateau
 * 
 * Classe pouvant contenir un évènement et un vaisseau ou un batiment.
 * C'est avec cette classe que le plateau intéragit pour savoir les
 * infos sur le vaisseau, batiment ou l'évènement contenu sur cette case
 */
class Cellule {
    
    public:
        /// Constructeur par défaut
        Cellule();
        bool possedeEvenement();
        const DetailEvenement& getEvenement();
        bool possedeBatiment();
        const DetailBatiment& getBatiment();
        bool possedeVaisseau();
        const DetailVaisseau& getVaisseau();
        void echangerVaisseau(Cellule cellule);
            
    private:
        VaisseauPtr getPointeurVaisseau();
        EvenementPtr evenement;
        BatimentPtr batiment;
        VaisseauPtr vaisseau;
        TypeCellule type;
        
};

#endif /* CELLULE_HPP */ 

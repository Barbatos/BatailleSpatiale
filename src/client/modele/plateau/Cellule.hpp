#ifndef CELLULE_HPP
#define CELLULE_HPP
#include "Evenement.hpp"
#include "CelluleBits.hpp"
#include "../structures/Batiment.hpp"
#include "../structures/Vaisseau.hpp"
#include "../../../commun/enum/TypeCellule.hpp"

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
        const DetailEvenement& getEvenement() const;

        bool possedeBatiment();
        const DetailBatiment& getBatiment() const;

        bool possedeVaisseau();
        const DetailVaisseau& getVaisseau() const;
        void setVaisseau(Vaisseau* _vaisseau);
        void echangerVaisseau(Cellule& cellule);

        void setType(TypeCellule _type);

        void setParcourable(bool parcourable = true);
        bool getParcourable() const;

        void setEstChemin(bool estChemin = true);
        bool getEstChemin() const;

        void setEstConstructibleVaisseau(bool estConstructible = true);
        bool getEstConstructibleVaisseau() const;

        void setEstConstructibleBatiment(bool estConstructible = true);
        bool getEstConstructibleBatiment() const;

        void setEstAttaquable(bool estAttaquable = true);
        bool getEstAttaquable() const;

        void setEstAttaquee(bool estAttaquee = true);
        bool getEstAttaquee() const;

        void setEstDetruite(bool estDetruite = true);
        bool getEstDetruite() const;

        void setEstDestination(bool estDest = true);
        bool getEstDestination() const;

        void setEstVisible(bool estVisible = true);
        bool getEstVisible() const;

        /**
         * \brief Indique le type de la cellule
         * Si un vaisseau ou un batiment est present, alors elle retourne un type correspondant.
         * De même si un evenement est present.
         *
         * \return Le type de la cellule.
         */
        TypeCellule statutEmplacement() const;

    private:
        friend sf::Packet& operator >>(sf::Packet& paquet, Cellule& cellule);

        void setEvenement(Evenement* _evenement);
        void retirerEvenement();
        void setBatiment(Batiment* _batiment);
        void retirerBatiment();
        void retirerVaisseau();

        VaisseauPtr& getReferenceVaisseau();
        EvenementPtr evenement;
        BatimentPtr batiment;
        VaisseauPtr vaisseau;
        TypeCellule type;
        CelluleBits bits;

};

sf::Packet& operator >>(sf::Packet& paquet, Cellule& cellule);

#endif /* CELLULE_HPP */

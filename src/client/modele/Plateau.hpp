#ifndef PLATEAU_CLIENT_HPP
#define PLATEAU_CLIENT_HPP
#include <vector>
#include "plateau/Cellule.hpp"
#include "../../commun/utile/Position.hpp"

/**
 * \brief Le plateau
 */
class Plateau {

    public:
        /**
         * \brief Constructeur par défaut créé simplement un plateau vide
         */
        Plateau();

        /**
         * \brief Informe si le plateau possède un évènement a la position p
         *
         * \param p La position
         * \return vrai si le plateau en possède un à la position p
         */
        bool possedeEvenement(Position p);

        /**
         * \brief Retourne l'évènement a la position p
         *
         * \param p La position
         * \return L'évènement
         */
        const DetailEvenement& getEvenement(Position p);

        /**
         * \brief Informe si le plateau possède un batiment a la position p
         *
         * \param p La position
         * \return vrai si le plateau en possède un à la position p
         */
        bool possedeBatiment(Position p);

        /**
         * \brief Retourne le batiment a la position p
         *
         * \param p La position
         * \return Le batiment
         */
        const DetailBatiment& getBatiment(Position p);

        /**
         * \brief Informe si le plateau possède un vaisseau a la position p
         *
         * \param p La position
         * \return vrai si le plateau en possède un à la position p
         */
        bool possedeVaisseau(Position p);

        /**
         * \brief Retourne le vaisseau a la position p
         *
         * \param p La position
         * \return Le vaisseau
         */
        const DetailVaisseau& getVaisseau(Position p);

        /**
         * \brief Getter tailleX
         *
         * \return La taille horizontalement
         */
        const sf::Int32& getTailleX() const;

        /**
         * \brief Getter tailleY
         *
         * \return La taille verticalement
         */
        const sf::Int32& getTailleY() const;

        const Cellule& getCellule(Position p);

        void viderZoneParcourable();

        void viderChemin();

        void viderZoneConstructible();

        void viderZoneAttaquable();
        
        void viderZones();

    private:
        bool positionValide(Position p);
        /// Les cellules du plateau
        std::vector<std::vector<Cellule>> cellule;
        sf::Int32 tailleX; ///< Taille du plateau en X
        sf::Int32 tailleY; ///< Taille du plateau en Y

        friend sf::Packet& operator >>(sf::Packet& paquet, Plateau& plateau);
        friend class ReseauClient;
};

sf::Packet& operator >>(sf::Packet& paquet, Plateau& plateau);

#endif /* PLATEAU_CLIENT_HPP */

#ifndef PLATEAU_CLIENT_HPP
#define PLATEAU_CLIENT_HPP
#include <vector>
#include <string>
#include "Cellule.hpp"
#include "Position.hpp"

/**
 * \brief Le plateau coté client
 * 
 * Cette classe est l'unique classe que le client peut utiliser pour
 * intéragir avec le moteur.
 * 
 */
class Plateau {
    
    public:
        /// Constructeur par défaut il créé la connexion avec le serveur
        Plateau(std::string adresseServeur = "127.0.0.1");
        bool possedeEvenement(Position p);
        const DetailEvenement& getEvenement(Position p);
        bool possedeBatiment(Position p);
        const DetailBatiment& getBatiment(Position p);
        bool possedeVaisseau(Position p);
        const DetailVaisseau& getVaisseau(Position p);
        bool deplacerVaisseau(Position depart, Position arrivee);
        
    private:
        /// Les cellules du plateau
        std::vector<std::vector<Cellule>> cellule;
        int tailleX;///< Taille du plateau en X
        int tailleY;///< Taille du plateau en Y
        int numeroJoueur;///< Le numero du joueur sur ce client
};

#endif /* PLATEAU_CLIENT_HPP */ 

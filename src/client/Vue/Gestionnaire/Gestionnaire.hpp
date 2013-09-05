#ifndef GESTIONNAIRE_HPP
#define GESTIONNAIRE_HPP

#include "Etats/Etat.hpp"
#include "../Affichage/Affichage.hpp"

/**
 * Gestionnaire d'état, s'occupe de gérer les différents écrans du jeu.
 */
class Gestionnaire {
    public:
        //Constructeur.
        Gestionnaire(VueGraphique&);
        //Destructeur.
        ~Gestionnaire();
        
        //Change l'état actuel.
        void changer(Etat*);
        
        //Met à jour l'état actuel.
        void update(float);
        
        //Dessine l'état actuel.
        void draw(Affichage&);
    
    private:
        //L'état actuel.
        Etat* etatActuel;
        //Le gestionnaire de ressources.
        Ressources ressources;
        //Le gestionnaire des évènements.
        Evenements evenements;
};

#endif

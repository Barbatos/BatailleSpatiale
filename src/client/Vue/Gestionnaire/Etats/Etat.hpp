#ifndef ETAT_HPP
#define ETAT_HPP

#include "../../Affichage/Affichage.hpp"

class VueGraphique;

/**
 * Interface état, définit un état du jeu, et les fonctions qui lui sont liées.
 */
class Etat {
    
    public:
    
        //Constructeur.
        Etat(VueGraphique& vue);
        //Destructeur.
        virtual ~Etat();
        
        //Que faire lorsqu'on rentre dans l'état ( Créé les objets se trouvant dans cet état.
        virtual void enter() = 0;
        //Que faire lorsqu'on quitte cet état ( Détruit tout les objets présents dans cet état.
        virtual void leave() = 0;
        
        //Met à jour l'état.
        virtual void update(float) = 0;
        //Dessine l'état.
        virtual void draw(Affichage&) = 0;
    
    protected:
        VueGraphique& vue;
};

#endif

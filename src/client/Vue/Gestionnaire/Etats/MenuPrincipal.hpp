#ifndef MENUPRINCIPAL_HPP
#define MENUPRINCIPAL_HPP

#include "Etat.hpp"

class MenuPrincipal : public Etat {
    public:
        MenuPrincipal(VueGraphique& vue);
        ~MenuPrincipal();
        
        //Que faire lorsqu'on rentre dans l'état ( Créé les objets se trouvant dans cet état.
        virtual void enter();
        //Que faire lorsqu'on quitte cet état ( Détruit tout les objets présents dans cet état.
        virtual void leave();
        
        //Met à jour l'état.
        virtual void update(float);
        //Dessine l'état.
        virtual void draw(Affichage&);
};

#endif

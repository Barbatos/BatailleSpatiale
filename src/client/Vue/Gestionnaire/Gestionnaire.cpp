#include "Gestionnaire.hpp"
#include "../Vue/VueGraphique.hpp"

/**
 * Constructeur.
 */
Gestionnaire::Gestionnaire(){
    etatActuel = new MenuPrincipal();
}

/**
 * Destructeur.
 */
Gestionnaire::~Gestionnaire() {
    delete etatActuel;
}

/**
 * Change l'état actuel, remplace l'état actuel par l'état passé en paramètre.
 */
void Gestionnaire::changer(Etat* nouvelEtat) {
    //On quitte l'état actuel.
    etatActuel->leave();
    
    //On le remplace par le nouvel état.
    etatActuel = nouvelEtat;
    
    //On entre dans le nouvel état.
    etatActuel->enter();
}

/**
 * Met à jour l'état actuel.
 */
void Gestionnaire::update(float delta) {
    etatActuel->update(delta);
}

/**
 * Dessinne l'état actuel.
 */
void Gestionnaire::draw(Affichage& affichage) {
    etatActuel->draw(affichage);
}

sf::Texture* Gestionnaire::getTexture(std::string nom) {
    return ressources.getTexture(nom);
}

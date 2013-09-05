#include "Ressources.hpp"

/**
 * Constructeur.
 */
Ressources::Ressources() {}

/**
 * Destructeur.
 */
Ressources::~Ressources() {}

/**
 * Retourne la texture possédant la clé passée en paramètre. Si elle n'existe pas, elle sera automatiquement chargée.
 */
sf::Texture* Ressources::getTexture(std::string nom) {
    //Si cette texture n'existe pas.
    if(textures.count(nom) == 0)
        //Si le chargement échoue.
        if(!loadTexture(nom))
            //On renvoie un truc null.
            return (sf::Texture*)0;
    
    //Si tout est bon.
    
    //On la smooth un peu.
    textures[nom].setSmooth(true);
    
    //Et on la retourne.
    return &textures[nom];
}

/**
 * Charge la texture possédant le nom donné.
 */
bool Ressources::loadTexture(std::string nom) {
    
    //Si le chargement de la texture échoue.
    if(!textures[nom].loadFromFile("images/" + nom + ".jpg"))
        //On retourne que c'est pas bon.
        return false;
	
    //Sinon, elle est chargée, tout va bien.
    return true;
}

#ifndef RESSOURCES_HPP
#define RESSOURCES_HPP

#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <map>
#include <string>

/**
 * Classe Ressources, correspond à la classe qui va charger toutes les 
 * images, polices, musiques, et les donner aux objets en ayant besoin.
 */
class Ressources {
    public:
        //Constructeur.
        Ressources();
        //Destructeur.
        ~Ressources();
        
        //Accède à la texture possédant le nom qu'on donne.
        sf::Texture* getTexture(std::string);
	
    private:
        //Map de textures. La map permet d'assigner à un objet une clé, par exemple sous forme de string.
        std::map<std::string, sf::Texture> textures;
        //Charge la texture possédant le nom qu'on lui donne.
        bool loadTexture(std::string);
};

#endif

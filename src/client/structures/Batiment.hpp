#ifndef BATIMENT_HPP
#define BATIMENT_HPP
#include "DetailBatiment.hpp"
#include <memory>

/**
 * Classe qui définit les differents attributs
 * que possèdent les vaisseaux.
 */
class Batiment {

    public:
        Batiment(DetailBatiment _detail = {TypeBatiment::Inexistant, 0, 0, 0, 0, 0, 0.0f, 0, 0});
        const DetailBatiment& getDetail();
    
    private:
        DetailBatiment detail;

};

typedef std::shared_ptr<Batiment> BatimentPtr;


#endif // BATIMENT_HPP


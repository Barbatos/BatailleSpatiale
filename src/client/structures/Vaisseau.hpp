#ifndef VAISSEAU_HPP
#define VAISSEAU_HPP
#include "DetailVaisseau.hpp"
#include <memory>

/**
 * Classe qui définit les differents attributs
 * que possèdent les vaisseaux.
 */
class Vaisseau {

    public:
        Vaisseau(DetailVaisseau _detail = {TypeVaisseau::Inexistant, 0, 0, 0, 0, 0.0f, 0, 0, 0});
        const DetailVaisseau& getDetail();
    
    private:
        DetailVaisseau detail;

};

typedef std::shared_ptr<Vaisseau> VaisseauPtr;


#endif // VAISSEAU_HPP


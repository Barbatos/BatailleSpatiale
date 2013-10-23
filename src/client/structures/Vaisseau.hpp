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
        /**
         * \brief Constructeur par défaut
         * 
         */
        Vaisseau(DetailVaisseau _detail = (DetailVaisseau){TypeVaisseau::Inexistant, 0, 0, 0, 0, 0.0f, 0, 0, 0});
        /**
         * \brief Retourne les infos sur le vaisseau
         * 
         * \return Les détails du vaisseau
         */
        const DetailVaisseau& getDetail();
    
    private:
        /// Les détails du vaisseau
        DetailVaisseau detail;

};

typedef std::shared_ptr<Vaisseau> VaisseauPtr;


#endif // VAISSEAU_HPP


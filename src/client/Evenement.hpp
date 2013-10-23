#ifndef EVENEMENT_HPP
#define EVENEMENT_HPP
#include "DetailEvenement.hpp"
#include <memory>

/**
 * Classe qui définit les differents attributs
 * que possèdent les vaisseaux.
 */
class Evenement {

    public:
        /**
         * \brief Constructeur par défaut
         * 
         * \param _detail les détails de l'évenement
         */
        Evenement(DetailEvenement _detail = (DetailEvenement){TypeEvenement::Inexistant});
        
        /**
         * \brief Getter Détail
         * 
         * \return les détails de l'évenement
         */
        const DetailEvenement& getDetail();
    
    private:
        DetailEvenement detail;

};

typedef std::shared_ptr<Evenement> EvenementPtr;


#endif // EVENEMENT_HPP

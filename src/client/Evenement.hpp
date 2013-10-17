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
        Evenement(DetailEvenement _detail = {TypeEvenement::Inexistant});
        const DetailEvenement& getDetail();
    
    private:
        DetailEvenement detail;

};

typedef std::shared_ptr<Evenement> EvenementPtr;


#endif // EVENEMENT_HPP

#include "Vaisseau.hpp"

Vaisseau::Vaisseau() {

}

Vaisseau::Vaisseau(DetailVaisseau _detail) :
    detail(_detail) {

}

const DetailVaisseau& Vaisseau::getDetail() {
    return detail;
}

void Vaisseau::setDetail(DetailVaisseau _detail) {
    detail = _detail;
}

sf::Packet& operator >>(sf::Packet& paquet, Vaisseau& vaisseau) {
    DetailVaisseau detail;
    sf::Int16 typeVaisseau;
    paquet >> detail.vie >> detail.vieMax >> detail.bouclier
           >> detail.bouclierMax >> detail.bouclierTaux >> detail.rayonVisibilite
           >> detail.rayonAttaque >> detail.attaque >> detail.consommation
           >> detail.deplacementMax >> typeVaisseau;
    detail.type = static_cast<TypeVaisseau>(typeVaisseau);
    
    vaisseau.setDetail(detail);
    return paquet;
}

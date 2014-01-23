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
    sf::Uint16 typeVaisseau;
    paquet >> typeVaisseau >> detail.attaque
           >> detail.vie >> detail.vieMax >> detail.visibilite >> detail.rayonAttaque
           >> detail.bouclier >> detail.bouclierMax >> detail.bouclierTaux
           >> detail.consommation >> detail.distanceMax >> detail.idJoueur >> detail.prixEnergie >> detail.prixMateriaux;
    detail.type = static_cast<TypeVaisseau>(typeVaisseau);
    vaisseau.setDetail(detail);
    return paquet;
}

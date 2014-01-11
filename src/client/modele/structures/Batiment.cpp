#include "Batiment.hpp"

Batiment::Batiment() {

}

Batiment::Batiment(DetailBatiment _detail) :
  detail(_detail) {
      
}

const DetailBatiment& Batiment::getDetail() {
    return detail;
}

void Batiment::setDetail(DetailBatiment _detail) {
    detail = _detail;
}

sf::Packet& operator >>(sf::Packet& paquet, Batiment& batiment) {
    DetailBatiment detail;
    sf::Uint16 typeBatiment;
    paquet >> typeBatiment >> detail.attaque
           >> detail.vie >> detail.vieMax >> detail.visibilite
           >> detail.bouclier >> detail.bouclierMax >> detail.bouclierTaux
           >> detail.niveau;
    detail.type = static_cast<TypeBatiment>(typeBatiment);
    
    batiment.setDetail(detail);
    return paquet;
}

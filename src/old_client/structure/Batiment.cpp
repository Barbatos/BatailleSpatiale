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
    sf::Int16 typeBatiment;
    paquet >> detail.vie >> detail.vieMax >> detail.bouclier
           >> detail.bouclierMax >> detail.bouclierTaux >> detail.rayonVisibilite
           >> detail.rayonAttaque >> detail.attaque >> detail.niveau
           >> typeBatiment;
    detail.type = static_cast<TypeBatiment>(typeBatiment);
    
    batiment.setDetail(detail);
    return paquet;
}

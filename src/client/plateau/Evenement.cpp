#include "Evenement.hpp"

Evenement::Evenement() {

}

Evenement::Evenement(DetailEvenement _detail) :
    detail(_detail) {

}

const DetailEvenement& Evenement::getDetail() {
    return detail;
}

void Evenement::setDetail(DetailEvenement _detail) {
    detail = _detail;
}

sf::Packet& operator >>(sf::Packet& paquet, Evenement& evenement) {
    DetailEvenement detail;
    sf::Int16 typeEvenement;
    paquet >> detail.vie >> detail.coutDeplacement >> detail.multiplicateurAttaque
           >> detail.multiplicateurDegat >> typeEvenement;
    detail.type = static_cast<TypeEvenement>(typeEvenement);
    
    evenement.setDetail(detail);
    return paquet;
}

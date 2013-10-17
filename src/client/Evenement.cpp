#include "Evenement.hpp"

Evenement::Evenement(DetailEvenement _detail) :
  detail(_detail) {
    
}

const DetailEvenement& Evenement::getDetail() {
    return detail;
}

#include "Vaisseau.hpp"

Vaisseau::Vaisseau(DetailVaisseau _detail) :
  detail(_detail) {
    
}

const DetailVaisseau& Vaisseau::getDetail() {
    return detail;
}

#include "Batiment.hpp"

Batiment::Batiment(DetailBatiment _detail) :
  detail(_detail) {
      
}

const DetailBatiment& Batiment::getDetail() {
    return detail;
}

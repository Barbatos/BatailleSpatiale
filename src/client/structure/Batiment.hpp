#ifndef BATIMENT_HPP
#define BATIMENT_HPP
#include "DetailBatiment.hpp"
#include <memory>

/**
 * Classe qui définit les differents attributs
 * que possèdent les vaisseaux.
 */
class Batiment {

public:
    /**
     * \brief Constructeur vide
     * Attention ce constructeur ne met pas de valeur par défaut
     */
    Batiment();
    /**
     * \brief Constructeur par défaut
     * affecte les détails au batiment
     *
     * \param _detail Les détails
     */
    Batiment(DetailBatiment _detail);
    /**
     * \brief Retourne les infos sur le batiment
     *
     * \return Les détails du batiment
     */
    const DetailBatiment& getDetail();
    /**
     * \brief change les détails du batiment
     *
     * \param _detail Les nouveaux détails
     */
    void setDetail(DetailBatiment _detail);

private:
    DetailBatiment detail;

};

sf::Packet& operator >>(sf::Packet& paquet, Batiment& batiment);

typedef std::shared_ptr<Batiment> BatimentPtr;


#endif // BATIMENT_HPP

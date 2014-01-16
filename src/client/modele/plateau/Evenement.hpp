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
	/**
	 * \brief Constructeur vide
	 * Attention ce constructeur ne met pas de valeur par défaut
	 */
	Evenement();
	/**
	 * \brief Constructeur par défaut
	 *
	 * \param _detail les détails de l'évenement
	 */
	Evenement(DetailEvenement _detail);
	/**
	 * \brief Getter Détail
	 *
	 * \return les détails de l'évenement
	 */
	const DetailEvenement& getDetail();
	/**
	 * \brief change les détails de l'évenement
	 *
	 * \param _detail Les nouveaux détails
	 */
	void setDetail(DetailEvenement _detail);

private:
	DetailEvenement detail;
};

sf::Packet& operator >>(sf::Packet& paquet, Evenement& evenement);

typedef std::shared_ptr<Evenement> EvenementPtr;


#endif // EVENEMENT_HPP

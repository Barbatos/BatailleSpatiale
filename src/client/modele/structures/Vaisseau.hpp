#ifndef VAISSEAU_HPP
#define VAISSEAU_HPP
#include "DetailVaisseau.hpp"
#include <memory>
#include <SFML/Network.hpp>
/**
 * Classe qui définit les differents attributs
 * que possèdent les vaisseaux.
 */
class Vaisseau {
public:
	/**
	 * \brief Constructeur vide
	 * Attention ce constructeur ne met pas de valeur par défaut
	 */
	Vaisseau();
	/**
	 * \brief Constructeur par défaut
	 * affecte les détails au vaisseau
	 *
	 * \param _detail Les détails
	 */
	Vaisseau(DetailVaisseau _detail);
	/**
	 * \brief Retourne les infos sur le vaisseau
	 *
	 * \return Les détails du vaisseau
	 */
	const DetailVaisseau& getDetail();
	/**
	 * \brief change les détails du vaisseau
	 *
	 * \param _detail Les nouveaux détails
	 */
	void setDetail(DetailVaisseau _detail);
private:
	/// Les détails du vaisseau
	DetailVaisseau detail;
};
sf::Packet& operator >>(sf::Packet& paquet, Vaisseau& vaisseau);
typedef std::shared_ptr<Vaisseau> VaisseauPtr;
#endif // VAISSEAU_HPP

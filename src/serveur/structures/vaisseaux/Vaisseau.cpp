#include "Vaisseau.hpp"

Vaisseau::Vaisseau() :
		Structure(),
		type(),
		distanceMax(0),
		consommation(0)

{
}

Vaisseau::Vaisseau(int _vieMax, int _bouclierMax, float _bouclierTaux,
	int _visibilite, int _attaque, int _distanceMax, int _consommation,
	TypeVaisseau _type) :
		Structure(_vieMax, _bouclierMax, _bouclierTaux, _visibilite, _attaque),
		type(_type),
		distanceMax(_distanceMax),
		consommation(_consommation)

{
}

int Vaisseau::getConsommation() const
{
	return consommation;
}

// Setters

void Vaisseau::setConsommation(const int _consommation)
{
	consommation = _consommation;
}

void Vaisseau::afficher(std::ostream& fluxSortant) const
{

	fluxSortant
		<< "Vie : "
		<< vie
		<< "/"
		<< vieMax
		<< std::endl
		<< "Bouclier : "
		<< bouclier
		<< "/"
		<< bouclierMax
		<< std::endl
		<< "% degats absorbes : "
		<< (bouclierTaux * 100)
		<< "%"
		<< std::endl
		<< "Visibilite : "
		<< visibilite
		<< std::endl
		<< "Attaque : "
		<< attaque
		<< std::endl
		<< "Consommation : "
		<< consommation
		<< std::endl
		<< std::endl;

}

std::ostream& operator<<(std::ostream& fluxSortant, Vaisseau const& Vaisseau)
{

	Vaisseau.afficher(fluxSortant);
	return fluxSortant;

}

void Vaisseau::subir(Vaisseau const& attaquant)
{

	Vaisseau cAttaquant(attaquant);

	switch (cAttaquant.getType())
	{

		case TypeVaisseau::Chasseur:
			switch (type)
			{
				case TypeVaisseau::Bombardier:
					cAttaquant.setAttaque(cAttaquant.getAttaque() * 1.75);
					break;
				case TypeVaisseau::Croiseur:
					cAttaquant.setAttaque(cAttaquant.getAttaque() / 2);
					break;
				case TypeVaisseau::Destructeur:
					cAttaquant.setAttaque(cAttaquant.getAttaque() / 4);
					break;
				default:
					break;

			}
			break;

		case TypeVaisseau::ChasseurLourd:
			switch (type)
			{
				case TypeVaisseau::Bombardier:
					cAttaquant.setAttaque(cAttaquant.getAttaque() * 2.5);
					break;
				case TypeVaisseau::Destructeur:
					cAttaquant.setAttaque(cAttaquant.getAttaque() / 3);
					break;
				default:
					break;

			}
			break;

		case TypeVaisseau::Croiseur:
			switch (type)
			{
				case TypeVaisseau::Chasseur:
					cAttaquant.setAttaque(cAttaquant.getAttaque() * 3);
					break;
				case TypeVaisseau::Destructeur:
					cAttaquant.setAttaque(cAttaquant.getAttaque() / 2);
					break;
				default:
					break;
			}

			break;

		case TypeVaisseau::Traqueur:
			switch (type)
			{
				case TypeVaisseau::Leger:
					cAttaquant.setAttaque(cAttaquant.getAttaque() * 3);
					break;
				case TypeVaisseau::ChasseurLourd:
					cAttaquant.setAttaque(cAttaquant.getAttaque() * 1.5f);
					break;
				case TypeVaisseau::Croiseur:
					cAttaquant.setAttaque(cAttaquant.getAttaque() * 1.5f);
					break;
				case TypeVaisseau::Bombardier:
					cAttaquant.setAttaque(cAttaquant.getAttaque() * 1.5f);
					break;
				case TypeVaisseau::Destructeur:
					cAttaquant.setAttaque(cAttaquant.getAttaque() / 1.5f);
					break;
				default:
					break;

			}
			break;

		case TypeVaisseau::Destructeur:
			switch (type)
			{
				case TypeVaisseau::Leger:
					cAttaquant.setAttaque(cAttaquant.getAttaque() * 4);
					break;
				case TypeVaisseau::Traqueur:
					cAttaquant.setAttaque(cAttaquant.getAttaque() * 2);
					break;
				default:
					break;

			}
			break;

		default:
			break;
	}

	Structure::subir(cAttaquant);

}

/*
 void Vaisseau::subir(Batiment const& attaquant){
 Structure::subir(attaquant);

 }
 */

Vaisseau Vaisseau::cloner(Vaisseau const& modele, TechnologieStructure techS,
	TechnologieVaisseau techV)
{

	Structure base = Structure::cloner(modele, techS);

	return Vaisseau(
			base.getVieMax(),
			base.getBouclierMax(),
			base.getBouclierTaux(),
			base.getVisibilite(),
			base.getAttaque(),
			modele.getDistanceMax() + (modele.getDistanceMax() * 0.5 * techV
					.getNiveauDistance()),
			modele.getConsommation() - (modele.getConsommation() * 0.1 * techV
					.getNiveauConsommation()));

}

int Vaisseau::getDistanceMax() const
{
	return distanceMax;
}

TypeVaisseau Vaisseau::getType() const
{
	return type;
}

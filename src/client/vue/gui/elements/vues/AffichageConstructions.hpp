/*
 * AffichageConstructions.hpp
 *
 *  Created on: 26 janv. 2014
 *      Author: Gabriel
 */

#ifndef AFFICHAGECONSTRUCTIONS_HPP_
#define AFFICHAGECONSTRUCTIONS_HPP_

class AffichageConstructions : public Element {
public:
	AffichageConstructions();
	virtual ~AffichageConstructions();

private:
	sf::Sprite listeConstructions[];
};

#endif /* AFFICHAGECONSTRUCTIONS_HPP_ */

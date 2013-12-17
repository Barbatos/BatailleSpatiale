/*
 * Gui.cpp
 *
 *  Created on: 16 déc. 2013
 *      Author: Soinou
 */

#include "Gui.hpp"

#include <client/vue/Scene.hpp>

Gui::Gui(sf::RenderWindow* fenetre, Scene* scene) :
		elements(),
		messages(),
		horloge(),
		fenetre(fenetre),
		scene(scene)
{

}

Gui::~Gui()
{
	for (Element::Ptr element : elements)
		element.reset();

	elements.clear();

	if (fenetre != nullptr)
		delete fenetre;

	if (scene != nullptr)
		delete scene;
}

Scene* Gui::lireScene()
{
	return scene;
}

void Gui::ajouter(Element::Ptr element)
{
	elements.push_back(element);
}

void Gui::ajouter(Element* element)
{
	ajouter(Element::Ptr(element));
}

void Gui::ajouterMessage(int id)
{
	messages.push(id);
}

void Gui::traiter(sf::Event evenement)
{
	switch (evenement.type)
	{
		case sf::Event::MouseButtonPressed:
			// Pour tout les élements
			for (Element::Ptr element : elements)
			{
				// Si l'élement observe la souris
				if (element->observeSouris())
				{
					// On lui envoie l'évènement
					element->lireSouris()->pressionSouris(
							evenement.mouseButton.button);

					// Si c'est un clic gauche, on lui dit qu'il est appuyé
					if (element->lireSurvol() && evenement.mouseButton.button == sf::Mouse::Left)
						element->ecrireAppui(true);
				}
			}
			break;
		case sf::Event::MouseButtonReleased:
			// Pour tout les élements
			for (Element::Ptr element : elements)
			{
				// Si l'élement observe la souris
				if (element->observeSouris())
				{
					// On lui envoie l'évènement
					element->lireSouris()->relachementSouris(
							evenement.mouseButton.button);

					// Si il est appuyé et que c'est un clic gauche
					if (element->lireSurvol() && element->lireAppui() && evenement
							.mouseButton.button == sf::Mouse::Left)
					{
						// Il n'est plus appuyé
						element->ecrireAppui(false);

						// Mais il a été cliqué !
						element->lireSouris()->clicSouris();
					}
				}
			}
			break;
		case sf::Event::MouseMoved:
			// Pour tout les élements
			for (Element::Ptr element : elements)
			{
				// Si l'élement observe la souris
				if (element->observeSouris())
				{
					// On récupère la position de la souris
					sf::Vector2i position(evenement.mouseMove.x,
											evenement.mouseMove.y);

					// Si l'élement est survolé, mais ne contient pas la souris
					if (element->lireSurvol() && !element->contient(position))
					{
						// Il n'est plus survolé
						element->ecrireSurvol(false);
						// Il n'est plus appuyé
						element->ecrireAppui(false);
						// Et la souris en sort
						element->lireSouris()->sortieSouris(
								sf::Vector2f(position));
					}
					// Sinon, si il n'est pas survolé mais contient la souris
					else if (!element->lireSurvol() && element->contient(
							position))
					{
						// Il est survolé
						element->ecrireSurvol(true);

						// Et la souris y entre
						element->lireSouris()->entreeSouris(
								sf::Vector2f(position));
					}
				}
			}
			break;
		case sf::Event::MouseWheelMoved:
			// Pour tout les élements
			for (Element::Ptr element : elements)
			{
				// Si l'élement observe la souris
				if (element->observeSouris())
					// On lui envoie l'évenement
					element->lireSouris()->moletteSouris(
							evenement.mouseWheel.delta);
			}
			break;
		case sf::Event::KeyPressed:
			// Pour tout les élements
			for (Element::Ptr element : elements)
			{
				// Si l'élement observe le clavier
				if (element->observeClavier())
					// On lui envoie l'évènement
					element->lireClavier()->pressionTouche(evenement.key.code);
			}
			break;
		case sf::Event::KeyReleased:
			// Pour tout les élements
			for (Element::Ptr element : elements)
			{
				// Si l'élement observe le clavier
				if (element->observeClavier())
					// On lui envoie l'évènement
					element->lireClavier()->relachementTouche(
							evenement.key.code);
			}
			break;
		case sf::Event::TextEntered:
			// Pour tout les élements
			for (Element::Ptr element : elements)
			{
				// Si l'élement observe le clavier
				if (element->observeClavier())
					// On lui envoie l'évènement
					element->lireClavier()->entreeTexte(
							sf::Uint32(evenement.text.unicode));
			}
			break;
		default:
			break;
	}
}

bool Gui::obtenirMessage(int* id)
{
	// Si il n'y a pas de message
	if (messages.empty())
		// On renvoie faux
		return false;

	// On récupère le premier message et on le met à l'adresse donnée
	*id = messages.front();
	messages.pop();

	// On renvoie vrai
	return true;
}

void Gui::actualiser()
{
	// On stocke le nouveau temps de l'horloge
	sf::Time nouveau = horloge.restart();
	// On calcule le temps écoulé depuis le dernier appel
	float delta = nouveau.asMilliseconds();

	// On actualise tout les élements
	for (Element::Ptr element : elements)
		element->actualiser(delta);
}

void Gui::afficher()
{
	for (Element::Ptr element : elements)
		element->afficher(*fenetre);
}

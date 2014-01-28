/*
 * Gui.cpp
 *
 *  Created on: 16 déc. 2013
 *      Author: Soinou
 */

#include "Gui.hpp"

#include <client/vue/Scene.hpp>

#include <client/Jeu.hpp>

Gui::Gui(sf::RenderWindow* fenetre, Scene* scene)
                : elements(), messages(), horloge(), fenetre(fenetre), scene(scene) {

}

Gui::~Gui() {
    elements.clear();
    observateursSouris.clear();
    observateursClavier.clear();
}

Scene* Gui::lireScene() {
    return scene;
}

void Gui::ajouter(Element::Ptr element) {
    elements.push_back(element);
}

void Gui::ajouter(Element* element) {
    ajouter(Element::Ptr(element));
}

void Gui::ajouterObservateurSouris(ObservateurSouris* observateur) {
    observateursSouris.push_back(observateur);
}

void Gui::ajouterObservateurClavier(ObservateurClavier* observateur) {
    observateursClavier.push_back(observateur);
}

void Gui::ajouterMessage(Message message) {
    messages.push(message);
}

void Gui::envoyerPressionBoutonSouris(sf::Event::MouseButtonEvent evenement) {
    // Pour tout les éléments
    for (Element::Ptr element : elements) {
        if (element->lireVisible()) {
            // Si l'élement observe la souris
            if (element->observeSouris()) {
                // On lui envoie l'évènement
                element->lireSouris()->pressionSouris(evenement.button);

                // Si c'est un clic gauche, on lui dit qu'il est appuyé
                if (element->lireSurvol()) {
                    if (evenement.button == sf::Mouse::Left)
                        element->ecrireAppui(true);
                    else if (evenement.button == sf::Mouse::Right)
                        element->ecrireAppuiDroit(true);
                }
            }
        }
    }

    // Pareil pour les observateurs simples
    for (ObservateurSouris* observateur : observateursSouris) {
        observateur->pressionSouris(evenement.button);
    }
}

void Gui::envoyerRelachementBoutonSouris(sf::Event::MouseButtonEvent evenement) {
    // Pour tout les éléments
    for (Element::Ptr element : elements) {
        if (element->lireVisible()) {
            // Si l'élement observe la souris
            if (element->observeSouris()) {
                // On lui envoie l'évènement
                element->lireSouris()->relachementSouris(evenement.button);

                // Si il est appuyé et que c'est un clic gauche
                if (element->lireSurvol()) {

                    if (element->lireAppui() && evenement.button == sf::Mouse::Left) {
                        // Il n'est plus appuyé
                        element->ecrireAppui(false);
                        element->lireSouris()->clicSouris(false);
                    }
                    else if (element->lireAppuiDroit() && evenement.button == sf::Mouse::Right) {
                        element->ecrireAppuiDroit(false);
                        element->lireSouris()->clicSouris(true);
                    }
                }
            }
        }
    }

    for (ObservateurSouris* observateur : observateursSouris)
        observateur->relachementSouris(evenement.button);

}

void Gui::envoyerMouvementSouris(sf::Event::MouseMoveEvent evenement) {
    // Pour tout les éléments
    for (Element::Ptr element : elements) {
        if (element->lireVisible()) {
            // Si l'élement observe la souris
            if (element->observeSouris()) {
                // On récupère la position de la souris
                sf::Vector2i position(evenement.x, evenement.y);

                // Si l'élement est dans une vue, on récupère sa vraie position
                if (element->possedeVue()) {
                    // TODO: Optimiser un peu ça
                    sf::View* vue = element->lireVue();

                    sf::Vector2u taille = lireScene()->lireJeu().lireAffichage().getSize();

                    sf::FloatRect rect(vue->getViewport().left * taille.x, vue->getViewport().top
                                                       * taille.y, vue->getViewport().width
                                                       * taille.x, vue->getViewport().height
                                                       * taille.y);

                    if (rect.contains(sf::Vector2f(position)))
                        position = sf::Vector2i(fenetre->mapPixelToCoords(position, *element->lireVue()));
                }

                // Si l'élement est survolé, mais ne contient pas la souris
                if (element->lireSurvol() && !element->contient(position)) {
                    // Il n'est plus survolé
                    element->ecrireSurvol(false);
                    // Il n'est plus appuyé
                    element->ecrireAppui(false);
                    // Et la souris en sort
                    element->lireSouris()->sortieSouris(sf::Vector2f(position));
                }
                // Sinon, si il n'est pas survolé mais contient la souris
                else if (!element->lireSurvol() && element->contient(position)) {
                    // Il est survolé
                    element->ecrireSurvol(true);

                    // Et la souris y entre
                    element->lireSouris()->entreeSouris(sf::Vector2f(position));
                }
            }
        }
    }
}

void Gui::envoyerMoletteSouris(sf::Event::MouseWheelEvent evenement) {

    // Pour tout les éléments
    for (Element::Ptr element : elements) {
        if (element->lireVisible()) {
            // Si l'élement observe la souris
            if (element->observeSouris())
                // On lui envoie l'évenement
                element->lireSouris()->moletteSouris(evenement.delta);
        }
    }

    for (ObservateurSouris* observateur : observateursSouris)
        observateur->moletteSouris(evenement.delta);
}

void Gui::envoyerPressionToucheClavier(sf::Event::KeyEvent evenement) {

    // Pour tout les éléments
    for (Element::Ptr element : elements) {
        if (element->lireVisible()) {
            // Si l'élement observe le clavier
            if (element->observeClavier())
                // On lui envoie l'évènement
                element->lireClavier()->pressionTouche(evenement.code);
        }
    }

    for (ObservateurClavier* observateur : observateursClavier)
        observateur->pressionTouche(evenement.code);
}

void Gui::envoyerRelachementToucheClavier(sf::Event::KeyEvent evenement) {

    // Pour tout les éléments
    for (Element::Ptr element : elements) {
        if (element->lireVisible()) {
            // Si l'élement observe le clavier
            if (element->observeClavier())
                // On lui envoie l'évènement
                element->lireClavier()->relachementTouche(evenement.code);
        }
    }

    for (ObservateurClavier* observateur : observateursClavier)
        observateur->relachementTouche(evenement.code);
}

void Gui::envoyerTexteClavier(sf::Event::TextEvent evenement) {

    // Pour tout les éléments
    for (Element::Ptr element : elements) {
        if (element->lireVisible()) {
            // Si l'élement observe le clavier
            if (element->observeClavier())
                // On lui envoie l'évènement
                element->lireClavier()->entreeTexte(sf::Uint32(evenement.unicode));
        }
    }

    for (ObservateurClavier* observateur : observateursClavier)
        observateur->entreeTexte(evenement.unicode);
}

void Gui::traiter(sf::Event evenement) {
    switch (evenement.type) {
        case sf::Event::MouseButtonPressed:
            envoyerPressionBoutonSouris(evenement.mouseButton);
            break;
        case sf::Event::MouseButtonReleased:
            envoyerRelachementBoutonSouris(evenement.mouseButton);
            break;
        case sf::Event::MouseMoved:
            envoyerMouvementSouris(evenement.mouseMove);
            break;
        case sf::Event::MouseWheelMoved:
            envoyerMoletteSouris(evenement.mouseWheel);
            break;
        case sf::Event::KeyPressed:
            envoyerPressionToucheClavier(evenement.key);
            break;
        case sf::Event::KeyReleased:
            envoyerRelachementToucheClavier(evenement.key);
            break;
        case sf::Event::TextEntered:
            envoyerTexteClavier(evenement.text);
            break;
        default:
            break;
    }
}

bool Gui::obtenirMessage(Message* message) {
    // Si il n'y a pas de message
    if (messages.empty())
        // On renvoie faux
        return false;

    // On récupère le premier message et on le met à l'adresse donnée
    *message = messages.front();
    messages.pop();

    // On renvoie vrai
    return true;
}

void Gui::actualiser() {
    // On stocke le nouveau temps de l'horloge
    sf::Time nouveau = horloge.restart();
    // On calcule le temps écoulé depuis le dernier appel
    float delta = nouveau.asMilliseconds();

    // On actualise tout les éléments
    for (Element::Ptr element : elements)
        element->actualiser(delta);
}

void Gui::afficher() {
    for (Element::Ptr element : elements) {
        if (element->lireVisible()) {
            if (element->possedeVue())
                fenetre->setView(*element->lireVue());

            element->afficher(*fenetre);

            fenetre->setView(fenetre->getDefaultView());
        }
    }
}

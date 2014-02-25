/*
 * Jeu.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include "Jeu.hpp"

#include <iostream>
#include <serveur/plateau/PlateauServeur.hpp>

#include <client/utile/Notification.hpp>

#define FPS 60
#define TEMPS_FRAME 1000/FPS

Jeu::Jeu() :
        modele(), controleur(modele), scene(nullptr), ressources(), horloge(), reseau(
                nullptr), joueur(NULL) {

    gestionnaire = new GestionnaireSons(&ressources);

    ressources.charger();

    affichage.creer();

    notification.ecrirePolice(ressources.lirePolice("grand9k.ttf"));

    changer(Scene::SceneMenuPrincipal);

    joueur = new Joueur();

    reseau = ReseauPtr(new ReseauClient(modele, *joueur));
    reseauActif = false;

    reseau->demanderListeServeurs();
}

Jeu::~Jeu() {
    if (scene != nullptr)
        scene.release();

    if (reseau != nullptr)
        reseau.release();

    if (serveur != nullptr)
        serveur->fermerReseau();

    delete gestionnaire;
    delete joueur;
}

void Jeu::changer(Scene::Type nouvelleScene) {
    if (scene != nullptr)
        scene.release();

    switch (nouvelleScene) {
        case Scene::SceneMenuPrincipal:
            scene = Scene::Ptr(new SceneMenuPrincipal(*this));
            break;
        case Scene::SceneJeu:
            scene = Scene::Ptr(new SceneJeu(*this));
            break;
        case Scene::SceneJeuMenu:
            scene = Scene::Ptr(new SceneJeuMenu(*this));
            break;
        case Scene::SceneJeuOptions:
            scene = Scene::Ptr(new SceneJeuOptions(*this));
            break;
        case Scene::SceneMenuSolo:
            scene = Scene::Ptr(new SceneMenuSolo(*this));
            break;
        case Scene::SceneMenuMulti:
            scene = Scene::Ptr(new SceneMenuMultijoueur(*this));
            break;
        case Scene::SceneOptionsMenu:
            scene = Scene::Ptr(new SceneOptionsMenu(*this));
            break;
        case Scene::SceneLancerServeur:
            scene = Scene::Ptr(new SceneLancerServeur(*this));
            break;
        case Scene::SceneListeServeurs:
            scene = Scene::Ptr(new SceneListeServeurs(*this));
            break;
        case Scene::SceneChargementJeu:
            scene = Scene::Ptr(new SceneChargementJeu(*this));
            break;
        case Scene::SceneChargementJeuMulti:
            scene = Scene::Ptr(new SceneChargementJeuMulti(*this));
            break;
        default:
            scene = Scene::Ptr(new SceneMenuPrincipal(*this));
            break;
    }
}

void Jeu::threadReseau() {
    while (true) {
        reseau->TraiterPaquetServeur();
        reseau->traiterPaquetMasterServeur();
        sf::sleep(sf::milliseconds(100));
    }
}

void Jeu::lancerServeurGUI(unsigned int port, bool partieSolo) {
    string nom = "Serveur GUI"; // TODO : proposer champ nom à la création d'un serveur

    plateauServeur = PlateauServeurPtr(new PlateauServeur(20, 20));
    plateauServeur->initialisationTest();
    serveur = ReseauServeurPtr(
            new ReseauServeur(port, *plateauServeur, nom, partieSolo));

    serveur->lancerReseau();
}

void Jeu::lancer() {
    sf::Event evenement;
    Message message;
    sf::Thread reseauThread(&Jeu::threadReseau, this);

    reseauThread.launch();

    while (affichage.isOpen()) {

        if(gestionnaire->lirePhaseDeJeu())
        {
        	gestionnaire->controlerIntensite();
        }

        while (affichage.pollEvent(evenement)) {
            if (evenement.type == sf::Event::Closed)
            affichage.close();

            scene->traiter(evenement);
        }

        while (scene->lireGui().obtenirMessage(&message)) {
            scene->surMessage(message);
        }

        affichage.clear();

        scene->actualiser();

        scene->afficher();

        affichage.display();
    }

    reseauThread.terminate();
}

void Jeu::quitter() {
    affichage.close();
}

Plateau& Jeu::lirePlateau() {
    return (modele);
}

Controleur& Jeu::lireControleur() {
    return (controleur);
}

Ressources& Jeu::lireRessources() {
    return (ressources);
}

ReseauPtr& Jeu::lireReseau() {
    return (reseau);
}
Joueur* Jeu::lireJoueur() {
    return (joueur);
}

GestionnaireSons* Jeu::lireGestionnaire() {
    return gestionnaire;
}

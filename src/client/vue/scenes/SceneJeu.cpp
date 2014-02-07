/*
 * sceneMenuPrincipal.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Kowah
 */

#include "SceneJeu.hpp"

#include <client/vue/gui/elements/vues/BoutonDeplacementPlateau.hpp>

#include <client/vue/gui/elements/vues/AffichageDetails.hpp>
#include <client/vue/gui/elements/vues/AffichageCase.hpp>
#include <client/vue/gui/elements/generiques/CaseACocher.hpp>

#include <client/Jeu.hpp>

#include <client/modele/Plateau.hpp>

SceneJeu::SceneJeu(Jeu& jeu)
                : Scene(jeu), vue(sf::FloatRect(0, 0, 0, 0)) {
    // On change le viewport de la vue
    vue.setViewport(sf::FloatRect(0.01f, 0.01f, 0.98f, 0.68f));

    GestionnaireSons* manager = jeu.lireGestionnaire();
    if(!manager->dejaEnCour(manager->lireRessources()->lireMusique("game_low.ogg")))
    {
    	manager->changerChanson(manager->chargerMusique("game_low.ogg"));
    	manager->lancerChanson();
    	manager->ecrirePhaseDeJeu(true);
    }

    gui.ajouterObservateurSouris(this);

    int winx = jeu.lireAffichage().getSize().x;
    int winy = jeu.lireAffichage().getSize().y;

    float x = winx * 0.01f;
    float y = winy * 0.01f;

    new Image(&gui, 100, 0, 0, winx, winy, jeu.lireRessources().lireImage("fond.png"));

    details = new AffichageDetails(&gui, Details, x, 0.7 * winy, winx - 2 * x, 0.3 * winy - y);

    initialiserPlateau();

    new BoutonDeplacementPlateau(&gui, Droite, winx - x, y, x, winy - 2 * y);
    new BoutonDeplacementPlateau(&gui, Gauche, 0, y, x, winy - 2 * y);
    new BoutonDeplacementPlateau(&gui, Haut, 0, 0, winx, y);
    new BoutonDeplacementPlateau(&gui, Bas, 0, winy - y, winx, y);

    new Bouton(&gui, Menu, "Menu", (winx - 100) / 2, winy - 40 - y, 100, 40);

    deplacement = new Bouton(&gui, Deplacement, "Deplacer", (winx + 20) / 2, 0.7 * winy, 100, 40);
    attaque = new Bouton(&gui, Attaque, "Attaquer", (winx - 230) / 2, 0.7 * winy , 100, 40);
    finTour = new Bouton(&gui, FinTour, "Fin du tour", (winx - 100) / 2, 0.8 * winy , 100, 40);

    sf::Color coche = sf::Color(50,50,50);
    sf::Color nonCoche = sf::Color(230,230,230);

    porteeDeplacement = new CaseACocher(&gui, PorteeDeplacement, x+10, y+10, 20, 20, "Afficher portee de deplacement", coche, nonCoche);
    porteeAttaque = new CaseACocher(&gui, PorteeAttaque, x+10, y+40, 20, 20, "Afficher portee d'attaque", coche, nonCoche);
    porteeConstruction = new CaseACocher(&gui, PorteeConstruction, x+10, y+70, 20, 20, "Afficher portee de construction", coche, nonCoche);

    porteeDeplacement->cocher();
    porteeAttaque->cocher();
    porteeConstruction->cocher();

    deplacement->ecrireVisible(false);
    attaque->ecrireVisible(false);
}

SceneJeu::~SceneJeu() {
    for (AffichageCase* c : cases)
        delete c;

    cases.clear();

    delete attaque;
    delete deplacement;
    delete finTour;
    delete porteeDeplacement;
    delete porteeAttaque;
    delete porteeConstruction;
}

void SceneJeu::initialiserPlateau() {

    // On récupère la taille de la fenêtre
    int winx = lireJeu().lireAffichage().getSize().x;
    int winy = lireJeu().lireAffichage().getSize().y;

    // On calcule la taille des boutons sur les côtés
    float x = winx * 0.01f;
    float y = winy * 0.01f;

    // On récupère le plateau
    Plateau & p = jeu.lirePlateau();

    p.viderZones();

    // On récupère les tailles du plateau
    int maxx = p.getTailleX();
    int maxy = p.getTailleY();

    // On initialise la taille des cellules
    int taille = 25;

    // On initialise les positions en x et y des cellules
    int xc = 0;
    int yc = 0;

    // On parcoure les cases du plateau
    for (int i = 0; i < maxx; i++)
        for (int j = 0; j < maxy; j++) {
            // On calcule la position en x et y
            xc = (i * 2 + j) * taille * 3 / 5;
            yc = j * taille;

            if (p.getCellule(Position(i, j)).statutEmplacement() != TypeCellule::Inexistant) {
                AffichageCase* c = new AffichageCase(&lireGui(), -1, xc, yc, taille, Position(i, j), &vue);

                // On ajoute la case à la liste de cases
                cases.push_back(c);
            }
        }

    // On change la taille de la vue
    if (xc > yc)
        taille = yc;
    else
        taille = xc;

    vue.setSize((winx - 2 * x) / 2, (winy - 2 * y) / 2);
    vue.move(taille / 2, taille / 2);
}

bool SceneJeu::valide(Cellule cellule) {
    return cellule.getEstAttaquable() || cellule.getParcourable()
                    || cellule.getEstConstructibleBatiment()
                    || cellule.getEstConstructibleVaisseau() || true;

    // TODO: Modifier une fois que la zone attaquable est fonctionnelle
}

void SceneJeu::appuiCase(Message::MessageCellule message) {

    // On récupère le plateau
    Plateau & p = lireJeu().lirePlateau();

    // Si c'est un message du plateau, on réinitialise tout
    if (message.x == -1 && message.y == -1) {
        p.viderZones();
        details->selectionner();
        deplacement->ecrireVisible(false);
        attaque->ecrireVisible(false);
        return;
    }

    // On récupère le réseau et les deux positions
    ReseauClient* r = lireJeu().lireReseau().get();
    Position selection = details->lirePosition();
    Position position = Position(message.x, message.y);

    // Si la destination correspond à la selection
    if ((selection.x == position.x && selection.y == position.y)
                    || !valide(p.getCellule(position))) {
        // On vide le chemin
        p.viderChemin();

        // On vide la destination
        p.viderDestination();

        // On cache le bouton d'action
        deplacement->ecrireVisible(false);
        attaque->ecrireVisible(false);

        // On réinitialise la destination
        destination = Position(-1, -1);
    }
    // Sinon, si c'est un clic droit, et une case était précédemment sélectionnée
    else if (message.clicDroit && selection.x != -1 && selection.y != -1) {
        // Si la selection est un vaisseau
        if (p.getCellule(selection).statutEmplacement() == TypeCellule::Vaisseau) {
            // On vide le chemin
            p.viderChemin();

            // On vide la destination
            p.viderDestination();

            switch (p.getCellule(position).statutEmplacement()) {
                case TypeCellule::Vide:
                    // Si la destination est une case vide

                    // On demande au réseau le chemin vers cette case
                    r->getChemin(selection, position);

                    // On affiche le bouton d'action en mode déplacer
                    deplacement->ecrireVisible(true);

                    //On cache le bouton d'attaque
                    attaque->ecrireVisible(false);
                    break;
                case TypeCellule::Vaisseau:
                case TypeCellule::Batiment:
                    // Si la destination est un vaisseau ou un bâtiment

                	//On montre le bouton d'attaque
                	attaque->ecrireVisible(true);

                	//On masque le bouton de déplacement pour bien expliciter au joueur
                	deplacement->ecrireVisible(false);
                    break;
                default:
                    break;
            }

            // On stocke la destination du joueur
            destination = position;

            r->setDestination(destination);
        }
    }

    // Si c'est un clic gauche
    if (!message.clicDroit) {

        // On vide les zones
        p.viderZones();

        // On sélectionne la position
        details->selectionner(position);

        // Si on a sélectionné un vaisseau
        if (p.getCellule(position).statutEmplacement() == TypeCellule::Vaisseau) {

            // On demande au réseau la zone parcourable, attaquable et constructible
        	if(porteeDeplacement->estCoche())
        		r->getZoneParcourable(position);

        	if(porteeConstruction->estCoche())
        		r->getZoneConstructibleBatiment(position);

        	if(porteeAttaque->estCoche())
        		r->getZoneAttaquable(position);
        }
        // Sinon, si c'est un bâtiment
        else if (p.getCellule(position).statutEmplacement() == TypeCellule::Batiment)
            // On demande au réseau la zone constructible
            r->getZoneConstructibleBatiment(position);
    }
}

void SceneJeu::effectuerAction() {
    // On récupère le plateau, le réseau, et l'ancienne position
    Plateau & p = lireJeu().lirePlateau();
    ReseauClient* r = lireJeu().lireReseau().get();
    Position ancienne = details->lirePosition();

    switch (p.getCellule(destination).statutEmplacement()) {
        case TypeCellule::Vide:
            // On demande le déplacement du vaisseau
            r->demanderDeplacementVaisseau(ancienne, destination);
            break;
        case TypeCellule::Batiment:
        case TypeCellule::Vaisseau:
            // On attaque le vaisseau
            r->demanderAttaqueVaisseau(ancienne, destination);
                        
            break;
        default:
            break;
    }

    // On vide les zones du plateau
    p.viderZones();

    // On vide le chemin
    p.viderChemin();

    // On cache le bouton d'action
    deplacement->ecrireVisible(false);
    attaque->ecrireVisible(false);

    // On vide la selection
    details->selectionner();

    // On vide la destination du joueur
    destination = Position(-1, -1);
}

void SceneJeu::surMessage(Message message) {

	Position pos;
    switch (message.type) {
        case Message::Element:
            switch (message.element.id) {
                case Menu:
                    jeu.changer(Scene::SceneJeuMenu);
                    break;
                case Droite:
                    if (vue.getCenter().x
                                    <= ((jeu.lirePlateau().getTailleX()
                                                    + jeu.lirePlateau().getTailleY() / 2) * 30))
                        vue.move(5, 0);
                    break;
                case Gauche:
                    if (vue.getCenter().x >= 0)
                        vue.move(-5, 0);
                    break;
                case Haut:
                    if (vue.getCenter().y >= 0)
                        vue.move(0, -5);
                    break;
                case Bas:
                    if (vue.getCenter().y
                                    <= ((jeu.lirePlateau().getTailleY()) * 25))
                        vue.move(0, 5);
                    break;
                case Deplacement:
                	effectuerAction();
                    break;
                case Attaque:
                	effectuerAction();
                	break;
                default:
                    break;
            }
            break;
        case Message::Cellule:
            appuiCase(message.cellule);
            break;
        default:
            break;
    }
}

// Héritées d'ElementSouris
void SceneJeu::clicSouris(bool) {
    /* Ne rien faire ici */
}

void SceneJeu::pressionSouris(sf::Mouse::Button) {
    /* Ne rien faire ici */
}

void SceneJeu::relachementSouris(sf::Mouse::Button bouton) {
    sf::Vector2u taille = lireJeu().lireAffichage().getSize();

    sf::FloatRect rect(vue.getViewport().left * taille.x, vue.getViewport().top * taille.y, vue.getViewport().width
                                       * taille.x, vue.getViewport().height * taille.y);

    if (!rect.contains(sf::Vector2f(sf::Mouse::getPosition())))
        return;

    if (bouton == sf::Mouse::Right)
        return;

    Message::MessageCellule message;

    message.x = -1;
    message.y = -1;

    message.clicDroit = false;
    message.selection = false;
    appuiCase(message);

}
void SceneJeu::entreeSouris(sf::Vector2f) {
    /* Ne rien faire ici */
}
void SceneJeu::sortieSouris(sf::Vector2f) {
    /* Ne rien faire ici */
}
void SceneJeu::moletteSouris(int delta) {
    if (delta <= 0 && vue.getSize().x < 2000)
        vue.zoom(1.1);
    else if (delta >= 0 && vue.getSize().x > 100)
        vue.zoom(0.9);
}

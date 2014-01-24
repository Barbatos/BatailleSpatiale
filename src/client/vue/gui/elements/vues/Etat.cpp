/*
 * Etat.cpp
 *
 *  Created on: 23 jan. 2014
 *      Author: Soinou
 */

#include "Etat.hpp"

#include <client/Jeu.hpp>
#include "AffichageDetails.hpp"

Etat::Etat(AffichageDetails* details, Jeu* jeu)
                : type(Normal), details(details), jeu(jeu) {

}

Etat::~Etat() {

}

void Etat::appuiCase(Message::MessageCellule message) {
    // On ajoute le message à notre file de messages
    messages.push(message);
}

void Etat::appuiPlateau() {
    switch (type) {
        case Normal:
            appuiNormal();
            break;
        case Selection:
            appuiSelection();
            break;
        case Construction:
            appuiConstruction();
            break;
        default:
            break;
    }
}

void Etat::appuiNormal() {

    std::cout << "Normal !" << std::endl;

    bool selection = false;
    bool clicDroit = false;
    Position position(-1, -1);

    while (!messages.empty()) {
        Message::MessageCellule message = messages.back();
        messages.pop();

        if (message.selection) {
            selection = true;
            clicDroit = message.clicDroit;
            position = Position(message.x, message.y);
        }

        std::cout << "Appui normal : " << " X : " << message.x << " Y : " << message.y << " CD : "
            << message.clicDroit << " S : " << message.selection << std::endl;

    }

    // On récupère les variables importantes
    Plateau& p = jeu->lirePlateau();
    ReseauClient* r = jeu->lireReseau().get();

    p.viderZoneParcourable();
    p.viderChemin();

    if (selection) {
        details->selectionner(position);

        r->getZoneParcourable(position);

        type = Selection;
    }
    else {
        details->selectionner();
    }

    /*

     // On vide les éventuels chemins
     p.viderChemin();
     p.viderZoneParcourable();

     // On sélectionne la position
     details->selectionner(position);

     // Si c'est un vaisseau, on affiche sa zone parcourable
     if (p.getCellule(position).statutEmplacement() == TypeCellule::Vaisseau)
     r->getZoneParcourable(position);

     // On teste si c'est un vaisseau constructeur
     bool constructeur = p.getCellule(position).statutEmplacement() == TypeCellule::Vaisseau
     && (p.getVaisseau(position).type == TypeVaisseau::Constructeur);

     // On teste si c'est un bâtiment constructeur
     bool batimentConstructeur = p.getCellule(position).statutEmplacement() == TypeCellule::Batiment
     && (p.getBatiment(position).type == TypeBatiment::Base);

     // Si c'est un vaisseau constructeur
     if (constructeur) {
     // On passe en mode construction
     type = Construction;

     r->getZoneConstructibleVaisseau(position);
     }
     // Si c'est un bâtiment constructeur
     else if (batimentConstructeur) {
     // On passe en mode construction
     type = Construction;

     // On récupère la zone constructible du bâtiment
     r->getZoneConstructibleBatiment(position);
     }
     // Sinon
     else
     // On passe en mode selection
     type = Selection;

     */
}

void Etat::appuiSelection() {

    std::cout << "Selection !" << std::endl;

    bool selection = false;
    bool clicDroit = false;
    Position position(-1, -1);

    while (!messages.empty()) {
        Message::MessageCellule message = messages.back();
        messages.pop();

        if (message.selection) {
            selection = true;
            clicDroit = message.clicDroit;
            position = Position(message.x, message.y);
        }

        std::cout << "Appui selection : " << " X : " << message.x << " Y : " << message.y
            << " CD : " << message.clicDroit << " S : " << message.selection << std::endl;

    }

    if (selection) {
        //details->selectionner(position);

        type = Normal;
    }
    else {
        details->selectionner();

        type = Normal;
    }

    /*
     // On récupère les variables importantes
     Plateau& p = jeu->lirePlateau();
     ReseauClient* r = jeu->lireReseau().get();
     Position ancienne = details->lirePosition();
     Position position = Position(message.x, message.y);

     std::cout << "Appui sélection : " << " X : " << message.x << " Y : " << message.y << " CD : "
     << message.clicDroit << " S : " << message.selection << std::endl;

     if (message.clicDroit) {
     // On vide les éventuels chemins
     p.viderChemin();
     p.viderZoneParcourable();

     r->getChemin(ancienne, position);
     r->getZoneParcourable(ancienne);
     }
     else {
     // Si c'est une déselection
     if (!message.selection) {
     // On déselectionne
     //details->selectionner();

     // On repasse en état normal
     //type = Normal;
     }
     // Sinon
     else {
     // Si la case est vide, on s'y déplace et on repasse en mode normal
     if (p.getCellule(position).statutEmplacement() == TypeCellule::Vide) {
     r->demanderDeplacementVaisseau(ancienne, position);

     details->selectionner();

     type = Normal;
     }
     // Sinon, on tente de l'attaquer
     else {
     // TODO: Méthode attaquer réseau
     // Pour l'instant on repasse en mode normal
     details->selectionner();

     type = Normal;
     }
     }
     }
     */
}

void Etat::appuiConstruction() {
    // On r�cup�re les variables importantes
    //Plateau& p = jeu->lirePlateau();
    //ReseauClient* r = jeu->lireReseau().get();
    //Position ancienne = details->lirePosition();
    //Position position = Position(message.x, message.y);
}

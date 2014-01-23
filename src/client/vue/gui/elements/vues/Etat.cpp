/*
* Etat.cpp
*
*  Created on: 23 jan. 2014
*      Author: Soinou
*/

#include "Etat.hpp"

#include <client/Jeu.hpp>
#include "AffichageDetails.hpp"

Etat::Etat(AffichageDetails* details, Jeu* jeu) : type(Normal), details(details), jeu(jeu) {

}

Etat::~Etat() {

}

void Etat::appuiCase(Message::MessageCellule message) {
    switch (type) {
        case Normal:
            appuiCase_Normal(message);
            break;
        case Selection:
            appuiCase_Selection(message);
            break;
        case Construction:
            appuiCase_Construction(message);
            break;
        default:
            break;
    }
}

void Etat::appuiCase_Normal(Message::MessageCellule message) {
    // Si c'est un clic droit, puisque rien n'est selectionné, on ne fait rien
    if (message.clicDroit)
        return;

    // Si ce n'est pas une selection, on ne fait rien
    if (!message.selection)
        return;

    // On récupère les variables importantes
    Plateau& p = jeu->lirePlateau();
    ReseauClient* r = jeu->lireReseau().get();
    Position position = Position(message.x, message.y);

    // On vide les éventuels chemins
    p.viderChemin();
    p.viderZoneParcourable();

    // On sélectionne la position
    details->selectionner(position);

    // Si c'est un vaisseau, on affiche sa zone parcourable
    if (p.getCellule(position).statutEmplacement() == TypeCellule::Vaisseau)
        r->getZoneParcourable(position);

    // On passe en mode selection
    type = Selection;
}

void Etat::appuiCase_Selection(Message::MessageCellule message) {
    // On récupère les variables importantes
    Plateau& p = jeu->lirePlateau();
    ReseauClient* r = jeu->lireReseau().get();
    Position ancienne = details->lirePosition();
    Position position = Position(message.x, message.y);

    if (message.clicDroit) {

    }
}

void Etat::appuiCase_Construction(Message::MessageCellule message) {

}
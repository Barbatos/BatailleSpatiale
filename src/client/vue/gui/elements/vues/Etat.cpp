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

    Plateau& p = jeu->lirePlateau();
    ReseauClient* r = jeu->lireReseau().get();
    Position ancienne = details->lirePosition();
    Position position = Position(message.x, message.y);

    // Si une case était précédemment selectionnée
    if (ancienne.x != -1 && ancienne.y != -1) {
        if (p.getCellule(ancienne).statutEmplacement() == TypeCellule::Vaisseau) {
            if (message.clicDroit) {
                p.viderChemin();
                r->getChemin(ancienne, position);
            }
            else {
                // Déplacement, Attaque, etc
                r->demanderDeplacementVaisseau(ancienne, position);
            }
        }
    }

    if (!message.clicDroit) {
        p.viderChemin();
        p.viderZoneParcourable();

        if (!message.selection && details->lirePosition() == position)
            details->selectionner();
        else if (message.selection) {
            details->selectionner(position);

            if (p.getCellule(position).statutEmplacement() == TypeCellule::Vaisseau)
                r->getZoneParcourable(position);
        }
    }
}

void Etat::appuiCase_Selection(Message::MessageCellule message) {

}

void Etat::appuiCase_Construction(Message::MessageCellule message) {

}
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

    // On teste si c'est un vaisseau constructeur
    bool constructeur = p.getCellule(position).statutEmplacement() == TypeCellule::Vaisseau;
    constructeur = constructeur && (p.getVaisseau(position).type == TypeVaisseau::Constructeur);

    // On teste si c'est un bâtiment constructeur
    bool batimentConstructeur = p.getCellule(position).statutEmplacement() == TypeCellule::Batiment;
    batimentConstructeur = batimentConstructeur
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

        // On r�cup�re la zone constructible du b�timent
        r->getZoneConstructibleBatiment(position);
    }
    // Sinon
    else
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
        r->getChemin(ancienne, position);
    }
    else {
        // Si c'est une déselection
        if (!message.selection) {
            // On déselectionne
            details->selectionner();

            // On repasse en état normal
            type = Normal;
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
}

void Etat::appuiCase_Construction(Message::MessageCellule) {
    // On r�cup�re les variables importantes
    //Plateau& p = jeu->lirePlateau();
    //ReseauClient* r = jeu->lireReseau().get();
    //Position ancienne = details->lirePosition();
    //Position position = Position(message.x, message.y);

    details->selectionner();

    type = Normal;
}

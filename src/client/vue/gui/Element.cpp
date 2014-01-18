/*
 * Element.cpp
 *
 *  Created on: 16 déc. 2013
 *      Author: Soinou
 */

#include "Element.hpp"

#include "Gui.hpp"

Element::Element(Gui* gui, int id)
: id(id), gui(gui), observateurSouris(nullptr),
observateurClavier(nullptr), survol(false), appui(false), vue(nullptr) {
    gui->ajouter(Ptr(this));
}

Element::~Element() {
    if (gui != nullptr)
        delete gui;

    if (vue != nullptr)
        delete vue;
}

ObservateurSouris* Element::lireSouris() {
    return observateurSouris;
}

ObservateurClavier* Element::lireClavier() {
    return observateurClavier;
}

void Element::enregistrerSouris(ObservateurSouris* observateur) {
    if (observateur == nullptr)
        return;

    observateurSouris = observateur;
}
void Element::enregistrerClavier(ObservateurClavier* observateur) {
    if (observateur == nullptr)
        return;

    observateurClavier = observateur;
}

bool Element::observeSouris() {
    return observateurSouris != nullptr;
}

bool Element::observeClavier() {
    return observateurClavier != nullptr;
}

int Element::lireId() {
    return id;
}

Gui* Element::lireGui() {
    return gui;
}

void Element::ecrireId(int id) {
    this->id = id;
}

void Element::ecrireGui(Gui* gui) {
    this->gui = gui;
}

sf::Vector2f Element::lireTaille() {
    return taille;
}

sf::Vector2f Element::lirePosition() {
    return position;
}

void Element::ecrireTaille(sf::Vector2f taille) {
    this->taille = taille;
}

void Element::ecrireTaille(float largeur, float hauteur) {
    ecrireTaille(sf::Vector2f(largeur, hauteur));
}

void Element::ecrirePosition(sf::Vector2f position) {
    this->position = position;
}

void Element::ecrirePosition(float x, float y) {
    ecrirePosition(sf::Vector2f(x, y));
}

void Element::ecrireZone(sf::FloatRect zone) {
    ecrirePosition(zone.left, zone.top);
    ecrireTaille(zone.width, zone.height);
}

bool Element::lireSurvol() {
    return survol;
}

bool Element::lireAppui() {
    return appui;
}

bool Element::lireAppuiDroit() {
    return appuiDroit;
}

sf::View* Element::lireVue() {
    return vue;
}

bool Element::possedeVue() {
    return vue != nullptr;
}

void Element::ecrireSurvol(bool survol) {
    this->survol = survol;
}

void Element::ecrireAppui(bool appui) {
    this->appui = appui;
}

void Element::ecrireAppuiDroit(bool appuiDroit) {
    this->appui = appuiDroit;
}

void Element::ecrireVue(sf::View* vue) {
    this->vue = vue;
}

void Element::envoyerMessage(Message message) {
    gui->ajouterMessage(message);
}

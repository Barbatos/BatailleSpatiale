/*
 * Notification.cpp
 *
 *  Created on: 12 févr. 2014
 *      Author: Soinou
 */

#include "Notification.hpp"

#include <client/vue/Affichage.hpp>

#define HAUTEUR_BOITE 20
#define BORDURE_BOITE 2

Notification* Notification::instance = nullptr;

Boite::Boite(std::wstring auteur, std::wstring message, int tempsAffichage,
        sf::Font& police) :
        cadre(), texte(), tempsAffichage(tempsAffichage), tempsEcoule(0) {
    texte.setString(auteur + L" : " + message);
    texte.setFont(police);
    texte.setCharacterSize(12);

    int largeur = texte.getGlobalBounds().width + 10;
    int hauteur = HAUTEUR_BOITE + 2 * BORDURE_BOITE;

    texte.setOrigin(largeur, hauteur);

    cadre.setSize(sf::Vector2f(largeur, hauteur));
    cadre.setFillColor(sf::Color(100, 100, 100));
    cadre.setOutlineColor(sf::Color(192, 192, 192));
    cadre.setOutlineThickness(BORDURE_BOITE);
    cadre.setOrigin(largeur, hauteur);
}

Boite::Boite(std::string auteur, std::string message, int tempsAffichage,
        sf::Font& police) :
        cadre(), texte(), tempsAffichage(tempsAffichage), tempsEcoule(0) {
    texte.setString(auteur + " : " + message);
    texte.setFont(police);
    texte.setCharacterSize(12);

    int largeur = texte.getGlobalBounds().width + 10;
    int hauteur = HAUTEUR_BOITE + 2 * BORDURE_BOITE;

    texte.setOrigin(largeur, hauteur);

    cadre.setSize(sf::Vector2f(largeur, hauteur));
    cadre.setFillColor(sf::Color(100, 100, 100));
    cadre.setOutlineColor(sf::Color(192, 192, 192));
    cadre.setOutlineThickness(BORDURE_BOITE);
    cadre.setOrigin(largeur, hauteur);
}

Boite::~Boite() {

}

void Boite::actualiser(float delta) {
    tempsEcoule += delta;

    int diff = tempsAffichage - tempsEcoule;

    if (diff <= 1000) {
        cadre.setFillColor(sf::Color(100, 100, 100, diff * 255 / 1000));
        cadre.setOutlineColor(sf::Color(192, 192, 192, diff * 255 / 1000));
        texte.setColor(sf::Color(255, 255, 255, diff * 255 / 1000));
    }
}

void Boite::afficher() {
    affichage.draw(cadre);
    affichage.draw(texte);
}

bool Boite::estTermine() {
    return tempsEcoule > tempsAffichage;
}

void Boite::ecrirePosition(int x, int y) {
    cadre.setPosition(x, y);

    texte.setPosition(x + 5,
            y + (cadre.getSize().y - texte.getCharacterSize()) / 2);
}

Notification::Notification() :
        boites() {
}

Notification::~Notification() {
}

void Notification::initialiser() {
    instance = new Notification();
}

void Notification::detruire() {
    delete instance;
}

void Notification::actualiser(float delta) {
    std::list<Boite::It> enlever;

    for (Boite::It boite = boites.begin(); boite != boites.end(); boite++) {
        (*boite).actualiser(delta);

        if ((*boite).estTermine())
            enlever.push_back(boite);
    }

    for (Boite::It boite : enlever) {
        boites.erase(boite);
    }

    int i = 0;
    int x = affichage.getSize().x - 5;
    int y = affichage.getSize().y - 5;

    int hauteur = (HAUTEUR_BOITE + 2 * BORDURE_BOITE + 5);

    for (Boite& boite : boites) {
        boite.ecrirePosition(x, y - i++ * hauteur);
    }
}

void Notification::afficher() {
    for (Boite& boite : boites) {
        boite.afficher();
    }
}

Notification& Notification::lireInstance() {
    return *instance;
}

void Notification::ecrirePolice(sf::Font& police) {
    this->police = police;
}

void Notification::ajouterMessage(std::wstring auteur, std::wstring message,
        int tempsAffichage) {
    boites.push_back(Boite(auteur, message, tempsAffichage, police));
}

void Notification::ajouterMessage(std::string auteur, std::string message,
        int tempsAffichage) {
    boites.push_back(Boite(auteur, message, tempsAffichage, police));
}

/*
 * Utile.cpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#include "Utile.hpp"

#include "Log.hpp"

#include <stdlib.h>
#include <time.h>
#include <sstream>

namespace Utile {
    void erreur(string endroit, string erreur) {
        fichierLog.ajouterLigne("Erreur à " + endroit + " : " + erreur);

        exit(-1);
    }

    string nomFichier(const string& cheminFichier) {
        size_t fin = cheminFichier.find_last_of('.');

        size_t debut = cheminFichier.find_last_of('/');

        if (fin == string::npos)
            fin = cheminFichier.length();

        if (debut == string::npos)
            debut = 0;
        else
            debut++;

        return (cheminFichier.substr(debut, fin - debut));
    }

    string extension(const string& nomFichier) {
        unsigned endroit = nomFichier.find_last_of('.');

        return (nomFichier.substr(endroit + 1));
    }

    string dateActuelle() {
        time_t courant = time(0);

        struct tm tstruct;

        char buffer[80];

        tstruct = *localtime(&courant);

        strftime(buffer, sizeof(buffer), "%Y-%m-%d.%X", &tstruct);

        return (buffer);
    }

    void redimensionnerImage(sf::Sprite& image, float largeur, float hauteur,
            bool proportions) {
        float largeurImage = image.getLocalBounds().width;
        float hauteurImage = image.getLocalBounds().height;
        float coeffX;
        float coeffY;

        coeffX = largeur / largeurImage;
        coeffY = hauteur / hauteurImage;

        if (hauteur < largeur && proportions)
            image.scale(coeffX, coeffX);
        else if (proportions)
            image.scale(coeffY, coeffY);
        else
            image.scale(coeffX, coeffY);
    }

    std::wstring convertir(TypeVaisseau type) {
        switch (type) {
            case TypeVaisseau::Inexistant:
                return L"Inexistant";
            case TypeVaisseau::Constructeur:
                return L"Constructeur";
            case TypeVaisseau::Bombardier:
                return L"Bombardier";
            case TypeVaisseau::Chasseur:
                return L"Chasseur";
            case TypeVaisseau::Croiseur:
                return L"Croiseur";
            case TypeVaisseau::Destructeur:
                return L"Destructeur";
            case TypeVaisseau::ChasseurLourd:
                return L"Chasseur Lourd";
            case TypeVaisseau::Traqueur:
                return L"Traqueur";
            case TypeVaisseau::Leger:
                return L"Léger";
            default:
                return L"";
        }
    }

    std::wstring convertir(TypeBatiment type) {
        switch (type) {
            case TypeBatiment::Base:
                return L"Base";
            case TypeBatiment::Raffinerie:
                return L"Raffinerie";
            default:
                return L"";
        }
    }

    std::wstring convertir(TypeEvenement type) {
        switch (type) {
            case TypeEvenement::ChampMeteor:
                return L"Champ de Météore";
            case TypeEvenement::Epave:
                return L"Epave";
            case TypeEvenement::InfluenceTrouNoir:
                return L"Influence trou noir";
            case TypeEvenement::NuageGaz:
                return L"Nuage de gaz";
            case TypeEvenement::StationSpatialeAbandonnee:
                return L"Station spatiale abandonnée";
            default:
                return L"";
        }
    }

    std::string lireFichier(TypeVaisseau type, int id) {
        std::stringstream stream;

        switch (type) {
            case TypeVaisseau::Inexistant:
                break;
            case TypeVaisseau::Constructeur:
                stream << "Vaisseaux/sprite_constructeur_1";
                break;
            case TypeVaisseau::Bombardier:
                stream << "Vaisseaux/sprite_bombardier_1";
                break;
            case TypeVaisseau::Chasseur:
                stream << "Vaisseaux/sprite_chasseur_1";
                break;
            case TypeVaisseau::Croiseur:
                stream << "Vaisseaux/sprite_croiseur_1";
                break;
            case TypeVaisseau::Destructeur:
                stream << "Vaisseaux/sprite_destroyeur_1";
                break;
            case TypeVaisseau::ChasseurLourd:
                stream << "Vaisseaux/sprite_chasseur_1";
                break;
            case TypeVaisseau::Traqueur:
                stream << "Vaisseaux/sprite_chasseur_1";
                break;
            case TypeVaisseau::Leger:
                stream << "Vaisseaux/sprite_chasseur_1";
                break;
            default:
                stream << "";
                break;
        }

        if (stream.str() == "")
            return "";

        if (id == 1)
            stream << "_rouge.png";
        else
            stream << "_bleu.png";

        return stream.str();
    }

    std::string lireFichier(DetailVaisseau details) {
        return lireFichier(details.type, details.idJoueur);
    }

    std::string lireFichier(TypeBatiment type, int id) {
        std::stringstream stream;

        switch (type) {
            case TypeBatiment::Base:
                stream << "Batiments/sprite_base_1";
                break;
            case TypeBatiment::Raffinerie:
                stream << "Batiments/sprite_raffinerie_1";
                break;
            case TypeBatiment::Mine:
                stream << "Batiments/sprite_super_satellite_1";
                break;
            case TypeBatiment::ChantierSpatial:
                stream << "Batiments/sprite_station_construction_1";
                break;
            default:
                stream << "";
                break;
        }

        if (stream.str() == "")
            return "";

        if (id == 1)
            stream << "_rouge.png";
        else
            stream << "_bleu.png";

        return stream.str();
    }

    std::string lireFichier(DetailBatiment details) {
        return lireFichier(details.type, details.idJoueur);
    }

    std::string lireFichier(DetailEvenement details) {
        std::string fichier;

        switch (details.type) {
            case TypeEvenement::ChampMeteor:
                break;
            case TypeEvenement::Epave:
                break;
            case TypeEvenement::InfluenceTrouNoir:
                break;
            case TypeEvenement::NuageGaz:
                break;
            case TypeEvenement::StationSpatialeAbandonnee:
                break;
            default:
                break;
        }

        return fichier;
    }

    std::wstring toString(DetailBatiment details) {
        std::wstringstream stream;

        stream << "Niveau : " << details.niveau << "\n";

        stream << "Type : " << Utile::convertir(details.type) << "\n";

        stream << "Vie : " << details.vie << "/" << details.vieMax << "\n";

        stream << "Attaque : " << details.attaque << ". Rayon : "
                << details.rayonAttaque << "\n";

        stream << "Bouclier : " << details.bouclier << "/"
                << details.bouclierMax << " : " << details.bouclierTaux << "\n";

        return stream.str();
    }

    std::wstring toString(DetailVaisseau details) {
        std::wstringstream stream;

        stream << "Type : " << Utile::convertir(details.type) << "\n";

        stream << "Vie : " << details.vie << "/" << details.vieMax << "\n";

        stream << "Attaque : " << details.attaque << ". Rayon : "
                << details.rayonAttaque << "\n";

        stream << "Bouclier : " << details.bouclier << "/"
                << details.bouclierMax << " : " << details.bouclierTaux << "\n";

        stream << L"Déplacement : " << details.distanceMax
                << ". Consommation : " << details.consommation << "\n";

        return stream.str();
    }

    std::wstring toString(DetailEvenement details) {
        std::wstringstream stream;

        stream << "Type : " << Utile::convertir(details.type) << "\n";

        stream << L"Coût déplacement : " << details.coutDeplacement << "\n";

        return stream.str();
    }

    std::wstring toString(Position position) {
        std::wstringstream stream;

        stream << "Position : " << position.x << "," << position.y;

        return stream.str();
    }
}

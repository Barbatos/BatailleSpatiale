/*
 * Ressources.hpp
 *
 *  Created on: 3 oct. 2013
 *      Author: Soinou
 */

#ifndef RESSOURCES_HPP
#define RESSOURCES_HPP

// Includes SFML
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Includes de la stdlib
#include <map>
#include <string>
#include <memory>

#include "Splash.hpp"

/**
 * \brief Contient toutes les ressources du jeu
 *
 * Stocke toutes les ressources du jeu
 */
class Ressources
{
	public:
		//////////////////////////////////////
		/// <!-- Typedefs -->
		//////////////////////////////////////

		/**
		 * \brief Typedef d'un std::pair associant un std::string à une sf::Texture
		 */
		typedef std::pair<std::string, sf::Texture> TexturePair;

		/**
		 * \brief Typedef d'une std::map associant un std::string à une sf::Texture
		 */
		typedef std::map<std::string, sf::Texture> TextureMap;

		/**
		 * \brief Typedef d'une std::pair associant un std::string à une sf::Font
		 */
		typedef std::pair<std::string, sf::Font> FontPair;

		/**
		 * \brief Typedef d'une std::map associant un std::string à une sf::Font
		 */
		typedef std::map<std::string, sf::Font> FontMap;

		/**
		 * \brief Typedef d'une version shared_ptr d'une sf::Music
		 */
		typedef std::shared_ptr<sf::Music> MusicPtr;

		/**
		 * \brief Typedef d'une std::pair associant un std::string à un MusicPtr
		 */
		typedef std::pair<std::string, MusicPtr> MusicPair;

		/**
		 * \brief Typedef d'une std::map associant un std::string à un MusicPtr
		 */
		typedef std::map<std::string, MusicPtr> MusicMap;

		/**
		 * \brief Typedef d'une std::pair associant un sf::SoundBuffer à un sf::Sound
		 */
		typedef std::pair<sf::SoundBuffer, sf::Sound> SoundPair;

		/**
		 * \brief Typedef d'une std::map associant un std::string à une SoundPair
		 */
		typedef std::map<std::string, SoundPair> SoundMap;

	private:
		/**
		 * \brief Liste de textures
		 *
		 * Contient toutes les textures du jeu associées à un nom
		 */
		TextureMap textures;

		/**
		 * \brief Liste de polices
		 *
		 * Contient toutes les polices du jeu associées à un nom
		 */
		FontMap polices;

		/**
		 * \brief Liste de tout les sons du jeu
		 *
		 * Pareil que #textures
		 */
		SoundMap sons;

		/**
		 * \brief Liste de toutes les musiques du jeu
		 *
		 * Pareil que #textures
		 */
		MusicMap musiques;

		/**
		 * \brief Volume actuel des sons
		 *
		 * Le volume des sons
		 */
		int volumeSons;

		/**
		 * \brief Volume actuel des musiques
		 *
		 * Le volume des musiques
		 */
		int volumeMusiques;

		/**
		 * \brief Fonction de chargement, appelée dans un thread
		 */
		void threadChargement();

		/**
		 * \brief Charge l'image passée en paramètre
		 *
		 * Récupère le chemin complet vers une image et tente de la charger
		 *
		 * \param nomImage l'image à charger
		 */
		void chargerImage(std::string nomImage);

		/**
		 * \brief Charge la police passée en paramètre
		 *
		 * Pareil que chargerImage()
		 *
		 * \param nomPolice la police à charger
		 */
		void chargerPolice(std::string nomPolice);

		/**
		 * \brief Charge le son passé en paramètre
		 *
		 * Pareil que chargerImage()
		 *
		 * \param nomSon le son à charger
		 */
		void chargerSon(std::string nomSon);

		/**
		 * \brief Charge la musique passée en paramètre
		 *
		 * Pareil que chargerImage()
		 *
		 * \param nomMusique la musique à charger
		 */
		void chargerMusique(std::string nomMusique);

		/**
		 * \brief Charge les polices données
		 *
		 * Récupère une liste de chemin vers des polices, et les charge en mémoire
		 *
		 * \param fichiers les images à charger
		 */
		void chargerImages(std::vector<std::string> fichiers);

		/**
		 * \brief Charge les polices données
		 *
		 * Pareil que chargerImages()
		 *
		 * \param fichiers les polices à charger
		 */
		void chargerPolices(std::vector<std::string> fichiers);

		/**
		 * \brief Charge les sons donnés
		 *
		 * Pareil que chargerImages()
		 *
		 * \param fichiers les sons à charger
		 */
		void chargerSons(std::vector<std::string> fichiers);

		/**
		 * \brief Charge les musiques données
		 *
		 * Pareil que chargerImages()
		 *
		 * \param fichiers les musiques à charger
		 */
		void chargerMusiques(std::vector<std::string> fichiers);

	public:
		/**
		 * \brief Constructeur
		 *
		 * Construit une nouvelle instance de Ressources
		 */
		Ressources();

		/**
		 * \brief Destructeur
		 *
		 * Détruit une instance précédemment créée
		 */
		virtual ~Ressources();

		/**
		 * \brief Charge les ressources
		 */
		void charger();

		/**
		 * \brief Récupère l'image demandée, et la charge si elle n'existe pas
		 *
		 * Prends en paramètre le chemin vers une image
		 * ( exemple : Images/Vaisseau/Chasseur ),
		 * la charge si elle n'existe pas, puis la renvoie
		 *
		 * \param nomTexture le nom de la texture à chercher
		 */
		sf::Sprite lireImage(std::string nomTexture);

		/**
		 * \brief Récupère une image
		 *
		 * Pareil que lireImage()
		 *
		 * \param nomPolice le nom de la police à chercher
		 */
		sf::Font& lirePolice(std::string nomPolice);

		/**
		 * \brief Joue un son
		 *
		 * Joue le son donné en paramètre
		 *
		 * \param nomSon le nom du son à chercher
		 */
		void jouerSon(std::string nomSon);

		/**
		 * \brief Récupère une musique
		 *
		 * Pareil que lireImage()
		 *
		 * \param nomMusique le nom de la musique à chercher
		 */
		MusicPtr lireMusique(std::string nomMusique);

		/**
		 * \brief Change le volume des sons
		 *
		 * Modifie le volume de tout les sons présents dans la liste des ressources
		 *
		 * \param volume le nouveau volume
		 */
		void changerVolumeSons(int volume);

		/**
		 * \brief Change le volume des musiques
		 *
		 * Modifie le volume de toutes les musiques présentes dans la liste des ressources
		 *
		 * \param volume le nouveau volume
		 */
		void changerVolumeMusiques(int volume);

		/**
		 * \brief Change le volume global
		 *
		 * Modifie le volume de toutes les musiques et de tout les sons présents
		 * dans la liste des ressources
		 *
		 * \param volume le nouveau volume
		 */
		void changerVolumeGlobal(int volume);

		/**
		 * \class Ressources
		 *
		 * Gère les différentes ressources du jeu (Images, Polices, Sons, Musiques)
		 * Possède des fonctions publiques permettant de :
		 * 		-Récupérer des ressources (Images, Polices, Musiques)
		 * 		-Jouer un son
		 * 		-Changer le volume : des musiques, des sons, des deux
		 *
		 * Exemple d'utilisation :
		 *
		 \code
		 // La variable ressources est normalement initialisée dans Jeu, il n'y a donc pas besoin de la créer
		 Ressources ressources;

		 // Récupération d'une image
		 sf::Sprite image = ressources.lireImage("chemin/vers/image.png");
		 //... Utilisation du sprite ...//

		 // Récupération d'une police
		 sf::Font& police = ressources.lirePolice("chemin/vers/police.ttf");
		 //... Utilisation de la police ...//

		 // MusicPtr est un typedef défini dans ressources.hpp
		 MusicPtr musique = ressources.lireMusique("chemin/vers/musique.ogg");
		 musique.play();
		 musique.pause();
		 musique.play();
		 musique.stop();

		 // Jouer un son
		 ressources.jouerSon("chemin/vers/son.wav");

		 // Changement des différents volumes

		 // Volume du son et des musiques
		 ressources.changerVolumeGlobal(50);

		 // Volume des musiques
		 ressources.changerVolumeMusiques(10);

		 // Volume des sons
		 ressources.changerVolumeSons(30);
		 \endcode
		 */
};

#endif /* RESSOURCES_HPP_ */

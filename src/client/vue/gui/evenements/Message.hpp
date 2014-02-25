/*
 * Message.hpp
 *
 *  Created on: 17 janv. 2014
 *      Author: Soinou
 */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <commun/utile/Position.hpp>
#include <enums.hpp>

/**
 * \brief Correspond à un message envoyé par un élément graphique
 */
class Message {
    public:
        /**
         * \brief Message généré par un élément
         */
        struct MessageElement {
                int id; //!< L'id de l'élément qui a généré l'élement
                bool clic; //!< Si l'élement a été cliqué ou non
        };

        /**
         * \brief Message généré par une construction
         */
        struct MessageConstruction {
                TypeCellule type;
                union {
                        TypeVaisseau vaisseau;
                        TypeBatiment batiment;
                };
        };

        /**
         * \brief Message généré par une cellule
         */
        struct MessageCellule {
                int x; //!< Position en y de la case
                int y; //!< Position en x de la case
                bool selection; //!< Si la case a été selectionnée ou déselectionnée
                bool clicDroit; //!< Si c'est un clic droit ou un clic gauche qui a été effectué
        };

        /**
         * \brief Représente le type du message
         */
        enum Type {
            Element, //!< Element
            Cellule,  //!< Case
            Construction //!< Construction
        };

        /**
         * \brief Le type du message
         */
        Type type;

        union {
                MessageElement element; //!< Arguments envoyés par un élément
                MessageCellule cellule; //!< Arguments envoyés par une cellule
                MessageConstruction construction; //!< Arguments envoyés par une construction
        };
};

#endif /* MESSAGE_HPP */

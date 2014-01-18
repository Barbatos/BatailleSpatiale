/*
 * VuesPack.hpp
 *
 *  Created on: 16 déc. 2013
 *      Author: Soinou
 */

#ifndef VUESPACK_HPP
#define VUESPACK_HPP

// Inclus toutes les classes dont on pourrait avoir besoin pour créer une vue

///////////////////////////////////////////
///	SFML
///////////////////////////////////////////

#include <SFML/Graphics.hpp>

///////////////////////////////////////////
///	Gui/Element
///////////////////////////////////////////

#include <client/vue/gui/Gui.hpp>
#include <client/vue/gui/Element.hpp>

///////////////////////////////////////////
///	Evenements
///////////////////////////////////////////

#include <client/vue/gui/evenements/ObservateurSouris.hpp>
#include <client/vue/gui/evenements/ObservateurClavier.hpp>
#include <client/vue/gui/evenements/Message.hpp>

///////////////////////////////////////////
///	Utiles
///////////////////////////////////////////

#include <utiles.hpp>

///////////////////////////////////////////
///	Scene
///////////////////////////////////////////

#include <client/vue/Scene.hpp>

#endif /* VUESPACK_HPP */

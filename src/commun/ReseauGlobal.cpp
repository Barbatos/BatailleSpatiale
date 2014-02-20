#include "ReseauGlobal.hpp"

#include <client/utile/Notification.hpp>

bool ReseauGlobal::ReceptionPaquet(sf::TcpSocket& socket, sf::Packet& paquet,
        sf::Time) {
    if (socket.receive(paquet)) {
        return true;
    }

    else {
        return false;
    }
}

void ReseauGlobal::EnvoiPaquet(sf::TcpSocket& socket, sf::Packet& paquet) {

    if (socket.send(paquet) != sf::Socket::Done) {
#ifndef SERVEUR
        notification.ajouterMessage("[RESEAU]", "Erreur lors de l'envoi d'un paquet", 5000);
#else
        std::cout << "[RESEAU] : Erreur lors de l'envoi d'un paquet" << std::endl;
#endif
        return;
    }
}

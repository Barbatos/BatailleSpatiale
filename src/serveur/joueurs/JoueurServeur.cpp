#include "JoueurServeur.hpp"

JoueurServeur::JoueurServeur(void) :
    socket(NULL), pseudo("Anonymous"), ip(""), id(-1),
    commandement(100), requisition(125), energie(200), materiaux(300) {
    techS = TechnologieStructure();
    techB = TechnologieBatiment();
    techV = TechnologieVaisseau();

}

sf::TcpSocket* JoueurServeur::getSocket(void) {
    return this->socket;
}

string JoueurServeur::getPseudo(void) {
    return this->pseudo;
}

string JoueurServeur::getIp(void) {
    return this->ip;
}

sf::Uint16 JoueurServeur::getId(void) {
    return this->id;
}

sf::Int32 JoueurServeur::getCommandement(void) {
    return this->commandement;
}

sf::Int32 JoueurServeur::getRequisition(void) {
    return this->requisition;
}

sf::Int32 JoueurServeur::getEnergie(void) {
    return this->energie;
}

sf::Int32 JoueurServeur::getMateriaux(void) {
    return this->materiaux;
}

void JoueurServeur::setSocket(sf::TcpSocket* _socket) {
    this->socket = _socket;
}

void JoueurServeur::setPseudo(string _pseudo) {
    this->pseudo = _pseudo;
}

void JoueurServeur::setIp(string _ip) {
    this->ip = _ip;
}

void JoueurServeur::setId(sf::Uint16 _id) {
    this->id = _id;
}

void JoueurServeur::setCommandement(sf::Int32 _commandement) {
    this->commandement = _commandement;
}

void JoueurServeur::setRequisition(sf::Int32 _requisition) {
    this->requisition = _requisition;
}

void JoueurServeur::setEnergie(sf::Int32 _energie) {
    this->energie = _energie;
}

void JoueurServeur::setMateriaux(sf::Int32 _materiaux) {
    this->materiaux = _materiaux;
}

void JoueurServeur::ajouterVaisseau(VaisseauServeurPtr vaisseau) {
    vaisseau->setIdJoueur(id);
    listeVaisseaux.push_back(std::weak_ptr<VaisseauServeur>(vaisseau));
}

void JoueurServeur::ajouterBatiment(BatimentServeurPtr batiment) {
    batiment->setIdJoueur(id);
    listeBatiments.push_back(std::weak_ptr<BatimentServeur>(batiment));
}

void JoueurServeur::ajournerListeStructures() {
    for (std::list<std::weak_ptr<BatimentServeur>>::iterator batiment=listeBatiments.begin();
            batiment!=listeBatiments.end(); ++batiment)
        if(!batiment->expired())
            batiment = listeBatiments.erase(batiment);

    for (std::list<std::weak_ptr<VaisseauServeur>>::iterator vaisseau=listeVaisseaux.begin();
            vaisseau!=listeVaisseaux.end(); ++vaisseau)
        if(!vaisseau->expired())
            vaisseau = listeVaisseaux.erase(vaisseau);
}

sf::Packet& operator <<(sf::Packet& paquet, const JoueurServeur& joueur) {
    paquet << joueur.commandement << joueur.requisition
           << joueur.energie << joueur.materiaux;


    return paquet;
}

#include "JoueurServeur.hpp"

JoueurServeur::JoueurServeur(void) :
    socket(NULL), pseudo("Anonymous"), ip(""), id(-1),
    commandement(100), requisition(125), energie(200), materiaux(300) {
    techS = TechnologieStructure();
    techB = TechnologieBatiment();
    techV = TechnologieVaisseau();




    ajouterConstructionVaisseau(VaisseauServeur(700, 300, 0.4f, 150, 250, 400, 100, 100, 500, 1000, TypeVaisseau::Chasseur));
    ajouterConstructionVaisseau(VaisseauServeur(500, 200, 0.2f, 200, 100, 600, 100, 100, 1000, 1000, TypeVaisseau::Constructeur));
    ajouterConstructionVaisseau(VaisseauServeur(2000, 800, 0.7f, 150, 800, 200, 200, 300, 1500, 3000, TypeVaisseau::Bombardier));
    ajouterConstructionVaisseau(VaisseauServeur(1300, 500, 0.6f, 150, 450, 350, 75, 200, 800, 1750, TypeVaisseau::Croiseur));
    ajouterConstructionVaisseau(VaisseauServeur(5000, 2500, 0.8f, 200, 1200, 50, 350, 150, 2500, 7000, TypeVaisseau::Destructeur));
    ajouterConstructionVaisseau(VaisseauServeur(1000, 500, 0.5f, 200, 375, 300, 150, 150,  800, 1500, TypeVaisseau::ChasseurLourd));
    ajouterConstructionVaisseau(VaisseauServeur(1500, 100, 0.9f, 300, 700, 800, 200, 300,  1300, 3200, TypeVaisseau::Traqueur));

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

sf::Int32 JoueurServeur::getId(void) {
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

VaisseauServeur JoueurServeur::getConstructionVaisseau(int index) {
    return listeConstructionVaisseau.at(index);
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

void JoueurServeur::setId(sf::Int32 _id) {
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
    listeVaisseaux.push_back(std::shared_ptr<VaisseauServeur>(vaisseau));
}

void JoueurServeur::ajouterBatiment(BatimentServeurPtr batiment) {
    batiment->setIdJoueur(id);
    listeBatiments.push_back(std::shared_ptr<BatimentServeur>(batiment));
}


void JoueurServeur::ajouterConstructionVaisseau(VaisseauServeur vaisseau) {
    listeConstructionVaisseau.push_back(vaisseau);
}

void JoueurServeur::retirerConstructionVaisseau() {
    if(!listeConstructionVaisseau.empty())
        listeConstructionVaisseau.pop_back();

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
    paquet << joueur.pseudo << joueur.commandement << joueur.requisition
           << joueur.energie << joueur.materiaux;


    return paquet;
}

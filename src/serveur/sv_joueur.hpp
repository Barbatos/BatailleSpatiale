#ifndef SV_JOUEUR_HPP
#define SV_JOUEUR_HPP

// Maximum de joueurs
#define MAX_JOUEURS 2

typedef struct {
	int 	numero;
	char 	pseudo[32];
	char 	ip[32];
	struct sockaddr *info;
} joueur_s;

//joueur_s joueurs[MAX_JOUEURS];

// Classe de gestion des joueurs.
class Joueur {

	public:
		void sayHello();
		void traiterDemandeConnexion(char *from);
		void traiterDemandeDeconnexion(char *from);

		static Joueur& Instance() {
			static Joueur singleton;
			return singleton;
		}
	protected:

	private:
		//Race race;
		std::string nom;
		int commandement;
		int construction;
		int requisition;
};

#endif

#ifndef VUE_HPP
#define VUE_HPP

/**
 * Interface Vue, générique d'une vue.
 */
class Vue {
	
	public:
		//Constructeur.
		Vue();
		//Destructeur.
		virtual ~Vue();
		//Initialiser la vue.
		virtual void initialiser() = 0;
		//Lancer la vue.
		virtual void lancer() = 0;
};

#endif

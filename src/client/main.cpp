#include "Vue/VueGraphique.hpp"

int main()
{    
    
    Vue* vue = new VueGraphique();

    vue->initialiser();
    
    vue->lancer();
    
    return 0;
}

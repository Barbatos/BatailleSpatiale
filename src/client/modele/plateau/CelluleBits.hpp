#ifndef CELLULE_BITS_HPP
#define CELLULE_BITS_HPP

struct CelluleBits {
    bool estParcourable : 1;
    bool estChemin : 1;
    bool estAttaquable : 1;
    bool estConstructibleVaisseau : 1;
    bool estConstructibleBatiment : 1;
};

#endif

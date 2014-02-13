#ifndef CELLULE_BITS_HPP
#define CELLULE_BITS_HPP

struct CelluleBits {
    bool estParcourable : 1;
    bool estChemin : 1;
    bool estAttaquable : 1;
    bool estConstructibleVaisseau : 1;
    bool estConstructibleBatiment : 1;
    bool estDestination : 1;
    bool estAttaquee : 1;
    bool estDetruite : 1;
    bool estVisible : 1;
};

#endif

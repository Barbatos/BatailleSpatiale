#ifndef CELLULE_BITS_H
#define CELLULE_BITS_H

struct CelluleBits {
	bool estParcourable : 1;
	bool estChemin : 1;
	bool estAttaquable : 1;
	bool estConstructibleVaisseau : 1;
	bool estConstructibleBatiment : 1;
};

#endif

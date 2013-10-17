#ifndef RACE_HPP
#define RACE_HPP

#include <list>
#include "../structures/Structure.hpp"

struct Race{
	
	char nom[20];
	
	Structure structure[1];
	
	std::list<int> vaisseaux;
	
	int requisitionDepart;
	
	int energieDepart;
	
	int constructionDepart;
	
	int commandementDepart;
	
};


const Race raceHumaine = {
	
	"Humain",
	
	{Structure()},
	
	std::list<int>({50,24,36})
	
};

#endif

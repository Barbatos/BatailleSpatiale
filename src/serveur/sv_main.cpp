#include "../global.hpp"

void SV_Frame(){
	char buffer[4096];
	char from[32];
	//char lol[1337];

	//sprintf(lol, "%d^Cleuuule", STC_CONNEXION);

	//@Charles - temporaire
	//Network::Instance().EnvoyerPaquet("5.135.157.11", lol, strlen(lol));

	memset(buffer, 0, sizeof(buffer));


	Network::Instance().RecevoirPaquet(from, buffer);
	Network::Instance().ParserRequete(from, buffer);
}

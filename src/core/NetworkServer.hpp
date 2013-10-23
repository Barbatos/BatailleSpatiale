#ifndef _NETWORK_SERVER_H_
#define _NETWORK_SERVER_H_

class NetworkServer
{

	public:
		NetworkServer(void);
		~NetworkServer(void);
		bool acceptNewClient(unsigned int & id);
		int receiveData(unsigned int client_id, char * recvbuf);
		void receiveFromClients();

		SOCKET ListenSocket;
		SOCKET ClientSocket;

		std::map<unsigned int, SOCKET> sessions;

	protected:
		sockaddr_in adresse; 

	private:
		char network_data[MAX_LONGUEUR_PAQUET];
};

#endif


#ifndef _NETWORK_CLIENT_H_
#define _NETWORK_CLIENT_H_

class NetworkClient
{

	public:
		void CloseSocket();
		NetworkClient(void);
		~NetworkClient(void);

		#ifdef _WIN32
		SOCKET 			ConnectSocket;
		#else
		int 			ConnectSocket;
		#endif
		

	protected:
		sockaddr_in 	adresse; // Paramètres de la connexion

};

#endif

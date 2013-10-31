#include "../../global.hpp"

void WaitForInput(void){
	string s;

	cout << "Please write something to send..." << endl;
	cin >> s;

	//NetworkGlobal::sendMessage()

}

void RunServer(unsigned short port){
	NetworkServer* server;

	server = new NetworkServer(port);

	for(;;){
		server->acceptNewClient();
		//WaitForInput();
		usleep(1000*100); // 100ms
	}
}

void RunClient(string ip, unsigned short port){
	NetworkClient* client;
	client = new NetworkClient(ip, port);
}

int main(){
	unsigned short port;
	char selection;
	string ip;

	cout << "NETWORK TEST - CLIENT-SERVER" << endl;

	cout << "Wanna launch a client (c) or a server (s) ?" << endl;
	cin >> selection;

	cout << "Which port ?" << endl;
	cin >> port;

	if(selection == 's'){

		RunServer(port);
	}

	else {
		cout << "Which IP?" << endl;
		cin >> ip;

		RunClient(ip, port);
	}
}

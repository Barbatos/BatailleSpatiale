#include "../../global.hpp"

NetworkClient* client;
NetworkServer* server;

void WaitForInput(void) {
	string s;
	sf::Packet packet;

	cout << "Please write something to send..." << endl;
	cin >> s;
	packet << s;

	NetworkGlobal::sendMessage(client->socket, packet);

}

void RunServer(unsigned short port) {

	server = new NetworkServer(port);

	for(;;) {
		server->acceptNewClient();
		usleep(1000*100); // 100ms
	}
}

void RunClient(string ip, unsigned short port) {
	client = new NetworkClient(ip, port);

	for(;;) {
		WaitForInput();
	}
}

int main() {
	unsigned short port = 1337;
	char selection;
	string ip = "localhost";

	cout << "NETWORK TEST - CLIENT-SERVER" << endl;

	cout << "Wanna launch a client (c) or a server (s) ?" << endl;
	cin >> selection;

	cout << "Which port ?" << endl;
	cin >> port;

	if(selection == 's') {

		RunServer(port);
	}

	else {
		cout << "Which IP?" << endl;
		cin >> ip;
		cout << "Connecting to " << ip << ":" << port << endl;

		RunClient(ip, port);
	}
}

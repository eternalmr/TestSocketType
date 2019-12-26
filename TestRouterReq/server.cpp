#pragma warning(disable:4996)

#include <zhelpers.hpp>

int main() {
	zmq::context_t context(1);
	zmq::socket_t server(context, ZMQ_REP);

	//  We use a string identity for ease here
	server.connect("tcp://localhost:5671");

	std::string reply = s_recv(server);
	std::cout << "Receive request: " << reply << std::endl;
	s_send(server, "do your work");

	system("pause");

	return 0;
}
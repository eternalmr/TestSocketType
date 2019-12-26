#pragma warning(disable:4996)

#include <zhelpers.hpp>

int main() {
	zmq::context_t context(1);
	zmq::socket_t server(context, ZMQ_REP);

	//  We use a string identity for ease here
	server.bind("tcp://*:5671");

	int work = 0;
	while (true)
	{
		std::string reply = s_recv(server);
		std::cout << "Receive request: " << reply << std::endl;
		s_send(server, std::to_string(work));
	}

	system("pause");

	return 0;
}
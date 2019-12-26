#pragma warning(disable:4996)

#include <zhelpers.hpp>

int main() {
	zmq::context_t context(1);
	zmq::socket_t client(context, ZMQ_REQ);

	//  We use a string identity for ease here
	client.connect("tcp://localhost:5671");

	s_send(client, "ready");
	std::string reply = s_recv(client);
	std::cout << "Receive reply: " << reply << std::endl;

	system("pause");

	return 0;
}
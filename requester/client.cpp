#pragma warning(disable:4996)

#include <zhelpers.hpp>

int main() {
	zmq::context_t context(1);
	zmq::socket_t client(context, ZMQ_REQ);
	client.connect("tcp://localhost:5671");

	for (int i = 0; i<3;++i) {
		std::cout << "**********************************************"<< std::endl;
		s_send(client, "ready");
		std::string reply = s_recv(client);
		std::cout << "Receive reply: " << reply << std::endl;

		// do some work
		int work = std::stoi(reply);
		for (; work < 20; ++work) {
			std::cout << "work: " << work << std::endl;
			Sleep(500);
		}
		std::cout << "**********************************************" << std::endl;
	}

	system("pause");

	return 0;
}
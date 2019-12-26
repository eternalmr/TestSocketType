#pragma warning(disable:4996)

#include <zhelpers.hpp>

int main() {
	zmq::context_t context(1);
	zmq::socket_t broker(context, ZMQ_ROUTER);

#if (defined(WIN32))
	broker.bind("tcp://*:5671"); // "ipc" doesn't yet work on windows.
#else
	broker.bind("ipc://routing.ipc");
#endif

	const int NBR_WORKERS = 2;

	//  Run for five seconds and then tell workers to end
	int64_t end_time = s_clock() + 5000;
	int workers_fired = 0;
	while (1) {
		//  Next message gives us least recently used worker
		std::string identity = s_recv(broker);
		s_recv(broker);     //  Envelope delimiter
		s_recv(broker);     //  Response from worker       

		s_sendmore(broker, identity);
		s_sendmore(broker, "");
		//  Encourage workers until it's time to fire them
		if (s_clock() < end_time)
			s_send(broker, "Work harder");
		else {
			s_send(broker, "Fired!");
			if (++workers_fired == NBR_WORKERS)
				break;
		}
	}

	system("pause");

	return 0;
}
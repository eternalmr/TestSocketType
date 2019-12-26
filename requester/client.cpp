#pragma warning(disable:4996)

#include <zhelpers.hpp>

int main() {
	zmq::context_t context(1);
	zmq::socket_t worker(context, ZMQ_REQ);

	//  We use a string identity for ease here
#if (defined (WIN32))
	s_set_id(worker, within(0x10000));
	worker.connect("tcp://localhost:5671"); // "ipc" doesn't yet work on windows.
#else
	s_set_id(worker);
	worker.connect("ipc://routing.ipc");
#endif

	int total = 0;
	while (1) {
		//  Tell the broker we're ready for work
		s_send(worker, "Hi Boss");
		

		//  Get workload from broker, until finished
		std::string workload = s_recv(worker);
		
		if ("Fired!" == workload) {
			std::cout << "Processed: " << total << " tasks" << std::endl;
			break;
		}
		total++;

		//  Do some random work
		s_sleep(within(500) + 1);
		std::cout << "Processing: Task " << total << std::endl;
	}

	system("pause");

	return 0;
}
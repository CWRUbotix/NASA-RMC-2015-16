#include "Network/CommTransmitter.hpp"

namespace Network {
	CommTransmitter::CommTransmitter() : Robos::NodeBase("CommTransmitter", "NetworkScheduler", std::vector<std::string>{"NetworkResponse"}, Async::Types::JobPriority::IMMEDIATE)
	{
		ip_address = ip;
 	}

 	CommTransmitter::~CommTransmitter()
	{
 	}

 	Robos::MessageBasePtr CommTransmitter::MainCallbackImpl(const Robos::MessageBasePtr pMessage)
	{
		std::shared_ptr<Robos:MessageBase> r;

 		initialize_server(5006, 100, ip_address);
		
		if(pMessage->topic == "NetworkResponse")
		{
			std::shared_ptr<Messages::MessageNetworkResponse> message = std::static_ptr_cast<Messages::MessageNetworkResponse>(pMessage);
			switch(message->response)
			{
				case none:
					return r;
					break;
				case successFail:
					if(message->success_fail)
					{
						send_command("Success");
					}
					else
					{
						send_command("Fail");
					}
					break;
				case verbose:
					char* verbose_response = (message->success_fail) ? "Success: " : "Failure: ";
					verbose_response += message->response_string;
					send_command(verbose_response, strlen(command) +1);
					break;
				default:
					return r;
					break;
			}
		}
		else
		{
			return r;
		}
	}
}

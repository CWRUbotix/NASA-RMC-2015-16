#include "Network/CommTransmitter.hpp"
#include "Messages/MessagesComm.hpp"

namespace Network {
	CommTransmitter::CommTransmitter(std::string ip) : Robos::NodeBase("CommTransmitter", "NetworkScheduler",
                                                                       std::vector<std::string>{"NetworkResponse"},
                                                                       Async::Types::JobPriority::IMMEDIATE), ip_address(ip)
	{
 	}

 	CommTransmitter::~CommTransmitter()
	{
 	}

 	Robos::MessageBasePtr CommTransmitter::MainCallbackImpl(const Robos::MessageBasePtr pMessage)
	{
		std::shared_ptr<Robos::MessageBase> r;

 		initialize_server(5006, 100, (char *)(ip_address.c_str()));
		
		if(pMessage->topic == "NetworkResponse")
		{
			std::shared_ptr<Messages::MessageNetworkResponse> message = std::static_pointer_cast<Messages::MessageNetworkResponse>(pMessage);
			switch(message->response)
			{
				case Network::Response::none:
					return r;
					break;
				case Network::Response::successFail:
					if(message->success_fail)
					{
						send_command((char *)"Success", strlen("Success") + 1);
					}
					else
					{
						send_command((char *)"Fail", strlen("Fail") + 1);
					}
					break;
				case Network::Response::verbose:
					char* verbose_response = (char *)((message->success_fail) ? "Success: " : "Failure: ");
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

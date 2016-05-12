#include "Messages/MessagesComm.hpp"
#include <string>

namespace Messages {
	MessageBaseCommand::MessageBaseCommand(Network::Response request, std::string topic) : Robos::MessageBase(topic)
	{
		response = request;
	}
	MessageBaseCommand::~MessageBaseCommand()
	{
	}

	MessageNetworkResponse::MessageNetworkResponse(Network::Response request, std::string topic, bool successful, char* verbose_string) : MessageBaseCommand(request, topic)
	{
		success_fail = successful;
		response_string = verbose_string;
	}
	MessageNetworkResponse::~MessageNetworkResponse()
	{
	}
}

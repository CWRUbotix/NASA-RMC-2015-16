#include "MessagesComm.hpp"
#include <string>

namespace Messages {
	MessageBaseCommand::MessageBaseCommand(Network::Response request, std::string topic) : Robos::MessageBase(topic), response(request)
	{
	}
	MessageBaseCommand::~MessageBaseCommand()
	{
	}		
}

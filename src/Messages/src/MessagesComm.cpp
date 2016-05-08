#include "MessagesComm.hpp"
#include <string>

namespace Network {
	MessageBaseCommand::MessageBaseCommand(Response request, std::string topic) : Robos::MessageBase(topic), response(request)
	{
	}
	MessageBaseCommand::~MessageBaseCommand()
	{
	}		
}

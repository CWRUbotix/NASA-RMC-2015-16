#pragma once
#ifndef MESSAGESCOMM_HPP_
#define MESSAGESCOMM_HPP_

#include <Robos/MessageBase.hpp>
#include <memory>
#include <string>
#include "CommonCommDataStructures.hpp"

namespace Messages {
	struct MessageBaseCommand : public Robos::MessageBase {
		Network::Response response;

		MessageBaseCommand(Network::Response response, std::string topic);
		~MessageBaseCommand();
	};
	
}

#endif

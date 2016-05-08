#pragma once
#ifndef MESSAGESCOMM_HPP_
#define MESSAGESCOMM_HPP_

#include <Robos/MessageBase.hpp>
#include <memory>
#include <string>

namespace Network {
	struct MessageBaseCommand : public Robos::MessageBase {
		Response response;

		MessageBaseCommand(Response response, std::string topic);
		~MessageBaseCommand();
	};
	
}

#endif

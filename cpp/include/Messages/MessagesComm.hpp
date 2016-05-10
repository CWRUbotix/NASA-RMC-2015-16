#pragma once
#ifndef MESSAGESCOMM_HPP_
#define MESSAGESCOMM_HPP_

#include <Robos/MessageBase.hpp>
#include <memory>
#include <string>
#include "CommonUtil/NetworkUtil.hpp"

namespace Messages {
	struct MessageBaseCommand : public Robos::MessageBase {
		Network::Response response;
		virtual char* serialized();
		virtual int len_serialized();
		virtual void fromPacket(char*,int);
		MessageBaseCommand(Network::Response, std::string);
		~MessageBaseCommand();
	};

	struct MessageNetworkResponse : public MessageBaseCommand {
		bool success_fail;
		char* response_string;
		MessageNetworkResponse(Network::Response, std::string, bool, char*);
		~MessageBaseCommand();
	};
}

#endif

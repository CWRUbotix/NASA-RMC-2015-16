#pragma once
#ifndef COMMTRANSMITTER_HPP_
#define COMMTRANSMITTER_HPP_

#include <string.h>
#include "Robos/NodeBase.hpp"
#include "Robos/MessageBase.hpp"
#include "server.h"
//#include "LibraryExport.hpp"

namespace Network {
class CommTransmitter : public Robos::NodeBase {
private:
	Robos::MessageBasePtr MainCallbackImpl(const Robos::MessageBasePtr pMessage) override;
public:
	CommTransmitter(std::string ip);
	~CommTransmitter();
	std::string ip_address;
};
}

 #endif /* COMMTRANSMITTER_HPP_ */

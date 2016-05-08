#pragma once
#ifndef COMM_RECIEVER
#define COMM_RECIEVER

#include <memory>
#include <Robos/InitNodeBase.hpp>
#include <Robos/MessageBase.hpp>
#include <sys/socket.h>
#include <string>
#include "LibraryExport.hpp"

namespace Network
{
	class NETWORKING_API CommReceiver : public Robos::InitNodeBase
	{
	private:
		virtual void MainCallbackImpl() override;
		std::string ip_address;

	public:
		CommReceiver(std::string ip);
		~CommReceiver();
	};

	using CommReceiverPtr = std::shared_ptr<CommReceiver>;
}

#endif

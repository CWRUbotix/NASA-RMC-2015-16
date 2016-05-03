#pragma once
#ifndef COMM_RECIEVER
#define COMM_RECIEVER

#include <memory>
#include <Robos/InitNodeBase.hpp>
#include <Robos/MessageBase.hpp>
#include <sys/socket.h>
#include "LibraryExport.hpp"

namespace Network
{
	class NETWORKING_API CommReciever : public Robos::InitNodeBase
	{
	private:
		virtual void MainCallbackImpl() override;

	public:
		CommReciever();
		~CommReciever();
	};

	using CommRecieverPtr = std::shared_ptr<CommReciever>;
}

#endif

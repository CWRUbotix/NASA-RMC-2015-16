#include <Robos/Robos.hpp>
#include <string>
#include <memory>
#include "Network/CommReceiver.hpp"
#include "Network/Network.hpp"
#include "Messages/MessagesMotorControl.hpp"
#include "Network/client.hpp"
#include "CommonUtil/NetworkUtil.hpp"

namespace Network
{
CommReceiver::CommReceiver(std::string ip) : Robos::InitNodeBase("CommReceiver", "NetworkScheduler")
{
	ip_address = ip;
}

CommReceiver::~CommReceiver()
{
}

void CommReceiver::MainCallbackImpl()
{
	//initialize connection here
	initialize_client(5005, 100, ip_address);

	char command[MAX_RECV_LEN];

	while(Robos::IsRunning() && (command[0] != 'q'))
	{
		//implement client code here
		//wait to recieve instruction and then send message to appropriate channel
		get_command(command);
		send_reply ("msg rcvd\n", strlen ("msg rcvd\n") + 1);
		Response response = none;
		//set response wanted
		switch (command[1])
		{
		case 0:
			response = none;
			break;

		case 1:
			response = successFail;
			break;

		case 2:
			response = verbose;
			break;

		default: //ERROR
		break;
		}

		std::shared_ptr<Robos::MessageBase> pMessage;
		switch (command[0])
		{
		case 1:
			pMessage = std::shared_ptr<Messages::MessageMotorAction>();
			std::static_pointer_cast<Messages::MessageMotorAction>(pMessage)->fromPacket(command+3,MAX_RECV_LEN-3);
			break;

		default:
			printf("ERROR: message recieved not formattted correctly");
			break;
		}
		this->PublishMessage(pMessage);
	}
	this->ShutdownRobos();
}
}

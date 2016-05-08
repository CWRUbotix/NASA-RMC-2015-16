#include <Robos/Robos.hpp>
#include <string>
#include "CommReceiver.hpp"
#include "Network.hpp"
#include "MessagesMotorControl.hpp"
#include "client.h"
#include "CommonCommDataStructures.hpp"

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

	char* command[MAX_RECV_LEN];

	while(Robos::IsRunning() && command[0] != 'q')
	{
		//implement client code here
		//wait to recieve instruction and then send message to appropriate channel
		command = get_command();
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

		auto pMessage;
		switch (command[0])
		{
		case 1:
			auto pMessage = std::make_shared<MessageMotorControl>();
			pMessage->serialized = command[2];
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

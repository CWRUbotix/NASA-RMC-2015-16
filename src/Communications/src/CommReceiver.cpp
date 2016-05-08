#include <Robos/Robos.hpp>

#include "CommReceiver.hpp"
#include "Network.hpp"
#include "MessagesMotorControl.hpp"
#include "client.h"
#include "CommonCommDataStructures.hpp"

namespace Network
{
	CommReceiver::CommReceiver() : Robos::InitNodeBase("CommReceiver", "NetworkScheduler")
	{
	}

	CommReceiver::~CommReceiver()
	{
	}

	void CommReceiver::MainCallbackImpl()
	{
		initialize_client(5005, 100, "192.168.0.1"); //IP address of computer, subject to change

		char* command[MAX_RECV_LEN];
		
		while(Robos::IsRunning() && command[0] != 'q')
		{
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

			//determine what type of command this is
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
		this->ShutdonwRobos();
	}
}

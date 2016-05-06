#include <Robos/Robos.hpp>

#include "CommReceiver.hpp"
#include "Network.hpp"
#include "MessagesMotorControl.hpp"
#include "client.h"

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
		//initialize connection here
		initialize_client(5005, 100, "192.168.0.1"); //IP address of computer, subject to change

		char* command[MAX_RECV_LEN];
		
		while(Robos::IsRunning() && command[0] != 'q')
		{
			//implement client code here
			//wait to recieve instruction and then send message to appropriate channel
			command = get_command();
			send_reply ("msg rcvd\n", strlen ("msg rcvd\n") + 1);

			switch (command[0])
			{
				case 1:
					auto pMessage = std::make_shared<MessageMotorControl>();
					

					pMessage->action = ; //MotorAction here
					break;

				default:
					printf("ERROR: message recieved not formattted correctly");
					break;
			}
			            
            		// parse out data from packets, set fields of message
			

         		// this->PublishMessage(pMessage);
		}
		this->ShutdonwRobos();
	}
}

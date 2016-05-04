#include <Robos/Robos.hpp>

#include "CommReciever.hpp"
#include "Network.hpp"
#include "Messages/MotorControlMessage.hpp"
#include "client.h"

namespace Network
{
	CommReciever::CommReciever() : Robos::InitNodeBase("CommReciever", "NetworkScheduler")
	{
	}

	CommReciever::~CommReciever()
	{
	}

	void CommReciever::MainCallbackImpl()
	{
		//initialize connection here
	        initialize_client(5005, 100, "192.168.0.1"); //IP address of control station, subject to change
		
		while(Robos::IsRunning())
		{
			//implement client code here
			//wait to recieve instruction and then send message to appropriate channel
			char* command = get_command();
			printf("%s", command);


			// auto pMessage = std::make_shared<ManualControl>();
            
		        // parse out data from packets, set fields of message
            
			// this->PublishMessage(pMessage);
		}
	}
}

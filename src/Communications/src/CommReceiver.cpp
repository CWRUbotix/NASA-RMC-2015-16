#include <Robos/Robos.hpp>

#include "CommReceiver.hpp"
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
        // initialize_client();
		
		while(Robos::IsRunning())
		{
			//implement client code here
			//wait to recieve instruction and then send message to appropriate channel
            // auto pMessage = std::make_shared<ManualControl>();
            
            // parse out data from packets, set fields of message
            

            // this->PublishMessage(pMessage);
		}
	}
}

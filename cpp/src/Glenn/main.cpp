// SYSTEM INCLUDES
#include <Robos/Robos.hpp>
#include <Network/CommTransmitter.hpp>
#include <Network/CommReceiver.hpp>
#include <MotorControl/MotorControlNode.hpp>
#include <Utilities/OSUtils.hpp>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <string.h>


// C++ PROJECT INCLUDES


int main(int argc, char** argv)
{
	// Connect to Team_02

	// Find router ip
	std::string my_ip = std::string("192.168.8.100");
	std::string router_ip = std::string("");
	char buff1[100];
	char buff2[20];
	char buff3[20];
	FILE *out = popen("route -n","r");
	fgets(buff1,sizeof(buff1)-1,out);
	fgets(buff1,sizeof(buff1)-1,out);
	while(::fgets(buff1,sizeof(buff1)-1,out)) {
		sscanf(buff1,"%s %s",buff2,buff3);
		if(std::string("0.0.0.0").compare(std::string(buff2)) == 0) {
			router_ip = std::string(buff3);
			break;
		}
	}

	// Find computers connected to router
	std::string ext_ip;
	bool found;
	restart:
	found = false;
	char cmd[120];
	strcpy(cmd, "nmap -sP ");
	strcat(cmd,buff3);
	strcat(cmd,"/24 | grep \"Nmap scan report for\" | awk '{print %5}'");
	out = popen(cmd,"r");
	while(fgets(buff1,sizeof(buff1)-1,out)) {
		if(std::string("192.168.8.1").compare(std::string(buff1))==0) {
			continue;
		}
		if(my_ip.compare(std::string(buff1))==0) {
			continue;
		}
		ext_ip = std::string(buff1);
		found = true;
	}
	// make a method, no time
	if(!found) {
		goto restart;
	}

	// initialize Nodes
	std::shared_ptr<Robos::NodeBase> pNetworkingClient = std::static_pointer_cast<Robos::NodeBase>(std::make_shared<Network::CommReceiver>());
	std::shared_ptr<Robos::NodeBase> pMotorController = std::static_pointer_cast<Robos::NodeBase>(std::make_shared<MotorControl::MotorNode>());

	// initialize Robos
	Robos::Init(Utilities::OS::GetCurrentDirectory(__FILE__) +
			Utilities::OS::GetPathSep() + "AsyncConfig.xml");

	// register Nodes with Robos
	Robos::Register(pNetworkingClient);
	Robos::Register(pMotorController);

	// Start Robos
	Robos::Start();

	// wait for timeout (or for a Node to kill)
	std::this_thread::sleep_for(std::chrono::seconds(10));
	// in the real version...call Robos::WaitForShutdown();
	// this thread will go to sleep until a Node makes a call to ShutdownRobos();
	// and then this thread will be woken up.

	// stop Robos
	Robos::Stop();
	return 0;
}

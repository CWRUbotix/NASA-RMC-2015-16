/*
 * AutonNode.cpp
 *
 *  Created on: Apr 30, 2016
 *      Author: Steven L
 */

 #include "CommTransmitter.hpp"

 namespace Network {
 	CommTransmitter::CommTransmitter() : Robos::NodeBase("CommTransmitter", "NetworkScheduler",
                                                         std::vector<std::string>{"Result", "ResultVerbose"},
                                                         Async::Types::JobPriority::IMMEDIATE){

 	}

 	CommTransmitter::~CommTransmitter(){

 	}

 	Robos::MessageBasePtr CommTransmitter::MainCallbackImp(const Robos::MessageBasePtr pMessage){
 		if(pMessage->topic == "Result"){
 			return nullptr;
 		}
 		if(pMessage->topic == "ResultVerbose"){
 			return nullptr;
 		}
 		throw std::logic_error("Unknown Message topic: " + pMessage->topic);
 	}
 }
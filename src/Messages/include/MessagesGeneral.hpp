#pragma once
#ifndef MESSAGESGENERAL_HPP_
#define MESSAGESGENERAL_HPP_

// SYSTEM INCLUDES
#include <Robos/MessageBase.hpp>

// C++ PROJECT INCLUDES


namespace Messages {

struct MessageSuccess : public Robos::MessageBase {
	MessageSuccess();
	~MessageSuccess();
};

struct MessageFailure : public Robos::MessageBase {
	MessageFailure();
	~MessageFailure();
};

struct MessageSuccessVerbose : public Robos::MessageBase
{
	char* successMessage;
	MessageSuccessVerbose(char* message);
	~MessageSuccessVerbose();
}

struct MessageFailureVerbose : public Robos::MessageBase
{
	char* failureMessage;
	MessageFailureVerbose(char* message);
	~MessageFailureVerbose();
}

} // end of namespace Messages

#endif // end of MESSAGESGENERAL_HPP_

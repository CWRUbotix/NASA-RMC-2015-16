// SYSTEM INCLUDES


// C++ PROJECT INCLUDES
#include "MessagesGeneral.hpp"

namespace Messages
{

    MessageSuccess::MessageSuccess() : Robos::MessageBase("Success")
    {
    }

    MessageSuccess::~MessageSuccess()
    {
    }

    MessageFailure::MessageFailure() : Robos::MessageBase("Failure")
    {
    }

    MessageFailure::~MessageFailure()
    {
    }

} // end of namespace Messages

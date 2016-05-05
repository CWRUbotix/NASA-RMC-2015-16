#ifndef MESSAGESGENERAL_HPP_
#define MESSAGESGENERAL_HPP_

namespace Messages {

struct MessageSuccess : public Robos::MessageBase {
	MessageSuccess();
	~MessageSuccess();
};

struct MessageFailure : public Robos::MessageBase {
	MessageFailure();
	~MessageFailure();
};

} // end of namespace Messages

#endif // end of MESSAGESGENERAL_HPP_

#ifndef SUBSCRIBER_H_
#define SUBSCRIBER_H_

#include "interface_subscriber.h"
#include "event_handler.h"

class subscriber_class : public isubscriber_class {
public:
    explicit subscriber_class(event_handler_class& _handler):m_handler(_handler){}
    ~subscriber_class(){}
    void subscribe(const subscription_struct& _subscription)  {
        m_handler.register_agent_to_floors_and_rooms(_subscription);
    }
private:
    event_handler_class& m_handler;
};

#endif /* SUBSCRIBER_H_ */
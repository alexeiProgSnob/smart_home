#ifndef SUBSCRIBER_H_
#define SUBSCRIBER_H_

#include "interface_subscriber.h"
#include "event_handler.h"

class SubscriberClass : public ISubscriberClass {
public:
    explicit SubscriberClass(EventHandlerClass& _handler):m_handler(_handler){}
    ~SubscriberClass(){}
    void Subscribe(const SubscriptionStruct& _subscription)  {
        m_handler.RegisterAgentToFloorsAndRooms(_subscription);
    }
private:
    EventHandlerClass& m_handler;
};

#endif /* SUBSCRIBER_H_ */
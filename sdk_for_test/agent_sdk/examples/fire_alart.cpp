#include "fire_alart.h"
#include "subscription.h"
#include <iostream>

fire_alart_class::fire_alart_class():m_runAgent(true) {
}

fire_alart_class::~fire_alart_class() {
}

void fire_alart_class::InitAgent(IPublisherClass& _publisher, ISubscriberClass& _subscriber) {
    std::cout<<"fire_alart init"<<std::endl;
    std::shared_ptr<AgentDataStruct> myData = GetAgentData();
    SubscriptionStruct fireDub(myData->m_floor, myData->m_room);
    auto call_back = [this](std::shared_ptr<EventClass> _event) { RecieveEvent(_event); };
    fireDub.SetCallBack(call_back);
    fireDub.SetType("Fire");
    
    _subscriber.Subscribe(fireDub);
}

void fire_alart_class::RunAgent() {
    std::cout<<"\nfire_agent start"<<std::endl;
    while (m_runAgent == true) {
        std::shared_ptr<EventClass> new_event = m_myRecievedEvents.Pop();
        std::cout<<"\nfire_agent"<<std::endl;
        std::cout<<"type "<<new_event->GetType()<<std::endl;
        std::cout<<"floor "<<new_event->GetFloor()<<std::endl;
        std::cout<<"level "<<new_event->GetLevel()<<std::endl<<std::endl;
    }
}

void fire_alart_class::RecieveEvent(std::shared_ptr<EventClass> _event) {
    std::cout<<"\nfire_agent recieve_event"<<std::endl;
    m_myRecievedEvents.Push(_event);
}

void fire_alart_class::ShutdownAgent() {
    m_runAgent = false;
    std::shared_ptr<EventClass> terminate_event(new EventClass("0", 0, "0", EventClass::HIGH));
    m_myRecievedEvents.Push(terminate_event);
}
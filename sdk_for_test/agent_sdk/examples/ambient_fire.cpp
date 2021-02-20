#include "ambient_fire.h"
#include <iostream>

AmbientFireClass::AmbientFireClass()
:m_publisher(nullptr),
 m_runAgent(true) {
}

AmbientFireClass::~AmbientFireClass() {
}

void AmbientFireClass::AlartOfFire() {
    std::shared_ptr<AgentDataStruct> myData = GetAgentData();
    while (m_runAgent == true) {
        std::shared_ptr<EventClass> fireEvent(new EventClass(
            "Fire",
            myData->m_floor,
            std::move(myData->m_room),
            EventClass::HIGH));
        std::this_thread::sleep_for(std::chrono::seconds(20));
        m_publisher->publish(fireEvent);
    }
}


void AmbientFireClass::InitAgent(IPublisherClass& _publisher, ISubscriberClass& _subscriber) {
    std::cout<<"InitAgent"<<std::endl;
    m_publisher = &_publisher;
}

void AmbientFireClass::RunAgent() {
    std::cout<<"ambient_fire run_agent"<<std::endl;
    AlartOfFire();
}

void AmbientFireClass::ShutdownAgent() {
    m_runAgent = false;
}
#include "ambient_fire.h"
#include <iostream>

ambient_fire_class::ambient_fire_class()
:m_publisher(nullptr),
 m_run_agent(true) {
}

ambient_fire_class::~ambient_fire_class() {
}

void ambient_fire_class::alart_of_fire() {
    std::shared_ptr<AgentDataStruct> my_data = get_agentData();
    while(m_run_agent == true) {
        std::shared_ptr<EventClass> fire_event(new EventClass(
            "Fire",
            my_data->m_floor,
            std::move(my_data->m_room),
            EventClass::HIGH));
        std::this_thread::sleep_for(std::chrono::seconds(20));
        m_publisher->publish(fire_event);
    }
}


void ambient_fire_class::InitAgent(IPublisherClass& _publisher, ISubscriberClass& _subscriber) {
    std::cout<<"InitAgent"<<std::endl;
    m_publisher = &_publisher;
}

void ambient_fire_class::run_agent() {
    std::cout<<"ambient_fire run_agent"<<std::endl;
    alart_of_fire();
}

void ambient_fire_class::shutdown_agent() {
    m_run_agent = false;
}
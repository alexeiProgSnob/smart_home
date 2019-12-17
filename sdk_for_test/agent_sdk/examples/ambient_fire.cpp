#include "ambient_fire.h"
#include <iostream>

ambient_fire_class::ambient_fire_class()
:m_publisher(nullptr),
 m_run_agent(true) {
}

ambient_fire_class::~ambient_fire_class() {
}

void ambient_fire_class::alart_of_fire() {
    std::shared_ptr<agent_data_struct> my_data = get_agent_data();
    while(m_run_agent == true) {
        std::shared_ptr<event_class> fire_event(new event_class(
            "Fire",
            my_data->m_floor,
            std::move(my_data->m_room),
            event_class::HIGH));
        std::this_thread::sleep_for(std::chrono::seconds(20));
        m_publisher->publish(fire_event);
    }
}


void ambient_fire_class::init_agent(ipublisher_class& _publisher, isubscriber_class& _subscriber) {
    std::cout<<"init_agent"<<std::endl;
    m_publisher = &_publisher;
}

void ambient_fire_class::run_agent() {
    std::cout<<"ambient_fire run_agent"<<std::endl;
    alart_of_fire();
}

void ambient_fire_class::shutdown_agent() {
    m_run_agent = false;
}
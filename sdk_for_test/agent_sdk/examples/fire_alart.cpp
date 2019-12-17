#include "fire_alart.h"
#include "subscription.h"
#include <iostream>

fire_alart_class::fire_alart_class():m_run_agent(true) {
}

fire_alart_class::~fire_alart_class() {
}

void fire_alart_class::init_agent(ipublisher_class& _publisher, isubscriber_class& _subscriber) {
    std::cout<<"fire_alart init"<<std::endl;
    std::shared_ptr<agent_data_struct> my_data = get_agent_data();
    subscription_struct fire_sub(my_data->m_floor, my_data->m_room);
    auto call_back = [this](std::shared_ptr<event_class> _event) { recieve_event(_event); };
    fire_sub.set_call_back(call_back);
    fire_sub.set_type("Fire");
    
    _subscriber.subscribe(fire_sub);
}

void fire_alart_class::run_agent() {
    std::cout<<"\nfire_agent start"<<std::endl;
    while(m_run_agent == true) {
        std::shared_ptr<event_class> new_event = m_my_recieved_events.pop();
        std::cout<<"\nfire_agent"<<std::endl;
        std::cout<<"type "<<new_event->get_type()<<std::endl;
        std::cout<<"floor "<<new_event->get_floor()<<std::endl;
        std::cout<<"level "<<new_event->get_level()<<std::endl<<std::endl;
    }
}

void fire_alart_class::recieve_event(std::shared_ptr<event_class> _event) {
    std::cout<<"\nfire_agent recieve_event"<<std::endl;
    m_my_recieved_events.push(_event);
}

void fire_alart_class::shutdown_agent() {
    m_run_agent = false;
    std::shared_ptr<event_class> terminate_event(new event_class("0", 0, "0", event_class::HIGH));
    m_my_recieved_events.push(terminate_event);
}
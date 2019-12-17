#include "hub.h"
#include <algorithm>
#include <signal.h>

namespace {
std::function<void(int)> shutdown_handler;
void signal_handler(int signal) { shutdown_handler(signal); }
} // end namespace

hub_class::hub_class()
:m_terminate(false),
m_subscriber(m_event_handler),
m_terminate_event(new event_class("terminate",0,"0", event_class::HIGH)) {
    shutdown_handler = [this](int signum) {
        if(signum == SIGINT) {
            m_publish.publish(m_terminate_event);
            m_terminate = true;
        }
    };
    signal(SIGINT, signal_handler);
}

hub_class::~hub_class() {
}

void hub_class::subscribe_for_terminate() {
    subscription_struct fire_sub(0, "0");
    auto call_back = [this](std::shared_ptr<event_class> _event) { 
        if(_event->get_type() == "terminate") {
            m_terminate = true;
        }
    };

    fire_sub.set_call_back(call_back);
    fire_sub.set_type("terminate");
    m_subscriber.subscribe(fire_sub);
}

void hub_class::init_hub_center(agents_container& _agents) {
    subscribe_for_terminate();

    m_thread_pool.init_thread_pool(_agents.size());
    auto init_do = [this](std::shared_ptr<agent_abstract_class>& _agent) { 
        _agent->init_agent(m_publish, m_subscriber);
        Task task = [_agent](){ _agent->run_agent(); };
        m_thread_pool.submit_task(alexei_prog_snob::thread_pool<Task>::MID, task);
    };
    std::for_each(_agents.begin(), _agents.end(), init_do);
}   

void hub_class::run_hub_center() {
    while (m_terminate != true) {
        std::shared_ptr<event_class> recieved_event = m_publish.get_event();
        m_event_handler.handle_event(recieved_event);
    }
}
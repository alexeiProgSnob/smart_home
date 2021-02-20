#include "hub.h"
#include <algorithm>
#include <signal.h>

namespace {
std::function<void(int)> shutdown_handler;
void signal_handler(int signal) { shutdown_handler(signal); }
} // end namespace

HubClass::HubClass()
:m_terminate(false),
m_subscriber(m_eventHandler),
m_terminateEvent(new EventClass("terminate",0,"0", EventClass::HIGH)) {
    shutdown_handler = [this](int signum) {
        if (signum == SIGINT) {
            m_publish.publish(m_terminateEvent);
            m_terminate = true;
        }
    };
    signal(SIGINT, signal_handler);
}

HubClass::~HubClass() {
}

void HubClass::p_SubscribeForTerminate() {
    SubscriptionStruct fireDub(0, "0");
    auto call_back = [this](std::shared_ptr<EventClass> _event) { 
        if (_event->GetType() == "terminate") {
            m_terminate = true;
        }
    };

    fireDub.SetCallBack(call_back);
    fireDub.SetType("terminate");
    m_subscriber.Subscribe(fireDub);
}

void HubClass::InitHubCenter(AgentsContainer& _agents) {
    p_SubscribeForTerminate();

    m_threadPool.InitThreadPool(_agents.size());
    auto init_do = [this](std::shared_ptr<AgentAbstractClass>& _agent) { 
        _agent->InitAgent(m_publish, m_subscriber);
        Task task = [_agent](){ _agent->RunAgent(); };
        m_threadPool.SubmitTask(alexei_prog_snob::ThreadPool<Task>::MID, task);
    };
    std::for_each(_agents.begin(), _agents.end(), init_do);
}   

void HubClass::RunHubCenter() {
    while (m_terminate != true) {
        std::shared_ptr<EventClass> recieved_event = m_publish.GetEvent();
        m_eventHandler.HandleEvent(recieved_event);
    }
}
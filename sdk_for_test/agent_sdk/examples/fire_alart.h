#ifndef FIRE_ALART_H_
#define FIRE_ALART_H_

#include "agent.h"
#include <memory>
#include <queue>
#include "safe_queue.h"

class fire_alart_class : public agent_abstract_class {
public:
    fire_alart_class();
    virtual ~fire_alart_class();
    virtual void init_agent(ipublisher_class& _publisher, isubscriber_class& _subscriber);
    virtual void run_agent();   
    virtual void recieve_event(std::shared_ptr<event_class> _event);
    virtual void shutdown_agent();
private:
//   isubscriber_class* m_sub;
    alexei_prog_snob::safe_queue<std::shared_ptr<event_class> > m_my_recieved_events;
    bool m_run_agent;
};


extern "C" agent_abstract_class* create() {
    return new fire_alart_class;
}
#endif /* FIRE_ALART_H_ */
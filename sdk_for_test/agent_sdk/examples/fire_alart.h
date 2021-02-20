#ifndef FIRE_ALART_H_
#define FIRE_ALART_H_

#include "agent.h"
#include <memory>
#include <queue>
#include "aps/templates/safe_queue.h"

class fire_alart_class : public AgentAbstractClass {
public:
    fire_alart_class();
    virtual ~fire_alart_class();
    virtual void InitAgent(IPublisherClass& _publisher, ISubscriberClass& _subscriber);
    virtual void run_agent();   
    virtual void recieve_event(std::shared_ptr<EventClass> _event);
    virtual void shutdown_agent();
private:
//   ISubscriberClass* m_sub;
    alexei_prog_snob::safe_queue<std::shared_ptr<EventClass> > m_my_recieved_events;
    bool m_run_agent;
};


extern "C" AgentAbstractClass* create() {
    return new fire_alart_class;
}
#endif /* FIRE_ALART_H_ */
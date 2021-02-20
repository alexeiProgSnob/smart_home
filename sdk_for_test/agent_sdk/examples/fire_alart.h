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
    virtual void RunAgent();   
    virtual void RecieveEvent(std::shared_ptr<EventClass> _event);
    virtual void ShutdownAgent();
private:
//   ISubscriberClass* m_sub;
    alexei_prog_snob::SafeQueue<std::shared_ptr<EventClass> > m_myRecievedEvents;
    bool m_runAgent;
};


extern "C" AgentAbstractClass* create() {
    return new fire_alart_class;
}
#endif /* FIRE_ALART_H_ */
#ifndef AMBIENT_FIRE_H_
#define AMBIENT_FIRE_H_

#include "agent.h"
#include <memory>
#include <thread>

class ambient_fire_class : public AgentAbstractClass {
public:
    ambient_fire_class();
    virtual ~ambient_fire_class();
   	virtual void InitAgent(IPublisherClass& _publisher, ISubscriberClass& _subscriber);
    virtual void run_agent();   
    virtual void shutdown_agent(); 
private:
    void alart_of_fire();    
    IPublisherClass* m_publisher;
    bool m_run_agent;
};

extern "C" AgentAbstractClass* create() {
    return new ambient_fire_class;
}




#endif /* AMBIENT_FIRE_H_ */
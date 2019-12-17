#ifndef AMBIENT_FIRE_H_
#define AMBIENT_FIRE_H_

#include "agent.h"
#include <memory>
#include <thread>

class ambient_fire_class : public agent_abstract_class {
public:
    ambient_fire_class();
    virtual ~ambient_fire_class();
   	virtual void init_agent(ipublisher_class& _publisher, isubscriber_class& _subscriber);
    virtual void run_agent();   
    virtual void shutdown_agent(); 
private:
    void alart_of_fire();    
    ipublisher_class* m_publisher;
    bool m_run_agent;
};

extern "C" agent_abstract_class* create() {
    return new ambient_fire_class;
}




#endif /* AMBIENT_FIRE_H_ */
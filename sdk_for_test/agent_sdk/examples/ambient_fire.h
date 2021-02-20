#ifndef AMBIENT_FIRE_H_
#define AMBIENT_FIRE_H_

#include "agent.h"
#include <memory>
#include <thread>

class AmbientFireClass : public AgentAbstractClass {
public:
    AmbientFireClass();
    virtual ~AmbientFireClass();
   	virtual void InitAgent(IPublisherClass& _publisher, ISubscriberClass& _subscriber);
    virtual void RunAgent();   
    virtual void ShutdownAgent(); 
private:
    void AlartOfFire();    
    IPublisherClass* m_publisher;
    bool m_runAgent;
};

extern "C" AgentAbstractClass* create() {
    return new AmbientFireClass;
}




#endif /* AMBIENT_FIRE_H_ */
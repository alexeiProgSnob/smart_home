#ifndef AGENT_H__
#define AGENT_H__

#include <stddef.h> 	/*< size_t >*/
#include <memory>		/*< std::shared_ptr<> >*/
#include "event.h"		/*< EventClass >*/

#include "interface_publisher.h"
#include "interface_subscriber.h"

typedef struct _AgentDataStruct{
	std::string m_name;
	std::string m_type;
	std::string m_room;
	size_t m_floor;
	std::string m_log;
	std::string m_config;
} AgentDataStruct;

class AgentAbstractClass {
public:
	AgentAbstractClass() {}
	virtual ~AgentAbstractClass() {}
	
	void SetAgentData(std::shared_ptr<AgentDataStruct>& _agentData) {
		m_agentData = _agentData;
	}

	virtual void InitAgent(IPublisherClass& _publisher, ISubscriberClass& _subscriber) = 0; 
	virtual void run_agent() = 0; 
	virtual void recieve_event(std::shared_ptr<EventClass> _event) {}
	virtual void shutdown_agent() {}
protected:
	std::shared_ptr<AgentDataStruct> get_agentData() {
		return m_agentData;
	}

private:
	std::shared_ptr<AgentDataStruct> m_agentData;
	
	// uncopyable
	AgentAbstractClass(const AgentAbstractClass&);
	AgentAbstractClass& operator=(const AgentAbstractClass&);
};

// Have to empliment in derived class by template AgentAbstractClass* creatr(){}
typedef AgentAbstractClass* creat_agent();


#endif /* AGENT_H__ */


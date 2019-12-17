#ifndef AGENT_H__
#define AGENT_H__

#include <stddef.h> 	/*< size_t >*/
#include <memory>		/*< std::shared_ptr<> >*/
#include "event.h"		/*< event_class >*/

#include "interface_publisher.h"
#include "interface_subscriber.h"

typedef struct _agent_data_struct{
	std::string m_name;
	std::string m_type;
	std::string m_room;
	size_t m_floor;
	std::string m_log;
	std::string m_config;
}agent_data_struct;

class agent_abstract_class {
public:
	agent_abstract_class() {}
	virtual ~agent_abstract_class() {}
	
	void set_agent_data(std::shared_ptr<agent_data_struct>& _agent_data) {
		m_agent_data = _agent_data;
	}

	virtual void init_agent(ipublisher_class& _publisher, isubscriber_class& _subscriber) = 0; 
	virtual void run_agent() = 0; 
	virtual void recieve_event(std::shared_ptr<event_class> _event) {}
	virtual void shutdown_agent() {}
protected:
	std::shared_ptr<agent_data_struct> get_agent_data() {
		return m_agent_data;
	}

private:
	std::shared_ptr<agent_data_struct> m_agent_data;
	
	// uncopyable
	agent_abstract_class(const agent_abstract_class&);
	agent_abstract_class& operator=(const agent_abstract_class&);
};

// Have to empliment in derived class by template agent_abstract_class* creatr(){}
typedef agent_abstract_class* creat_agent();


#endif /* AGENT_H__ */


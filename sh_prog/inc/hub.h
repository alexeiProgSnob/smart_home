#ifndef HUB_H_
#define HUB_H_

#include <vector>
#include <memory>

#include "event_handler.h"
#include "thread_pool.h"
#include "q_publisher.h"
#include "subscriber.h"
#include "agent.h"

class hub_class {
public:
	typedef typename std::vector<std::shared_ptr<agent_abstract_class> > agents_container;
	hub_class();
	~hub_class();
	void init_hub_center(agents_container& _agents);
	void run_hub_center();
private:
	typedef std::function<void()> Task;
	bool m_terminate;
	event_handler_class m_event_handler;
	queue_publisher_class m_publish; 
	subscriber_class m_subscriber;
	alexei_prog_snob::thread_pool<Task> m_thread_pool;
	std::shared_ptr<event_class> m_terminate_event;
	void subscribe_for_terminate();
};

#endif /* HUB_H_ */

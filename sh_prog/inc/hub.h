#ifndef HUB_H_
#define HUB_H_

#include <vector>
#include <memory>

#include "event_handler.h"
#include "aps/templates/thread_pool.h"
#include "q_publisher.h"
#include "subscriber.h"
#include "agent.h"

class HubClass {
public:
	typedef typename std::vector<std::shared_ptr<AgentAbstractClass> > AgentsContainer;
	HubClass();
	~HubClass();
	void InitHubCenter(AgentsContainer& _agents);
	void RunHubCenter();
private:
	typedef std::function<void()> Task;
	void p_SubscribeForTerminate();
	
	bool m_terminate;
	EventHandlerClass m_eventHandler;
	QueuePublisherClass m_publish; 
	SubscriberClass m_subscriber;
	alexei_prog_snob::ThreadPool<Task> m_threadPool;
	std::shared_ptr<EventClass> m_terminateEvent;
};

#endif /* HUB_H_ */

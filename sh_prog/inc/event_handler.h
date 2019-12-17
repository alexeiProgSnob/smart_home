#ifndef EVET_HANDLER_H__
#define EVET_HANDLER_H__

#include <functional> 		// std::function
#include <utility> 			// std::pair
#include <memory>			// std::shared_ptr
#include <vector> 			// std::vector
#include <map>				// std::map

#include "subscription.h"	// subscription_struct
#include "uncopyable.h"		// alexei_prog_snob::uncopyable_class
#include "event.h"			// event_class

class event_handler_class : private alexei_prog_snob::uncopyable_class {
public:
	/* @description : 	this typename is for all pairs of floor what rooms
						the agent want to register
	*/	
	event_handler_class();
	~event_handler_class();
	
	/* @description : 
	*/
	void register_agent_to_floors_and_rooms(const subscription_struct& _subscription);

	void handle_event(std::shared_ptr<event_class> _event);
private:
	typedef typename std::function<void(std::shared_ptr<event_class>)> agent_event_handle;
	typedef typename std::map<std::string, std::vector<agent_event_handle> > room_event_handles;
	typedef typename std::map<size_t, room_event_handles> floor_rooms_event_handles;
	typedef typename std::map<std::string, floor_rooms_event_handles> event_type_subs;

	event_type_subs m_subscriber_container;
};


#endif /* EVET_HANDLER_H__ */
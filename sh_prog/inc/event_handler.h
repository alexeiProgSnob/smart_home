#ifndef EVET_HANDLER_H__
#define EVET_HANDLER_H__

#include <functional> 		// std::function
#include <utility> 			// std::pair
#include <memory>			// std::shared_ptr
#include <vector> 			// std::vector
#include <map>				// std::map

#include "subscription.h"	// SubscriptionStruct
#include "event.h"			// EventClass

class EventHandlerClass {
public:
	/* @description : 	this typename is for all pairs of floor what rooms
						the agent want to register
	*/	
	EventHandlerClass();
	~EventHandlerClass();

	EventHandlerClass(const EventHandlerClass&) = delete;
	EventHandlerClass(EventHandlerClass&&) = delete;
	EventHandlerClass& operator=(const EventHandlerClass&) = delete;
	
	/* @description : 
	*/
	void RegisterAgentToFloorsAndRooms(const SubscriptionStruct& _subscription);

	void HandleEvent(std::shared_ptr<EventClass> _event);
private:
	typedef typename std::function<void(std::shared_ptr<EventClass>)> AgentEventHandle;
	typedef typename std::map<std::string, std::vector<AgentEventHandle> > RoomEventHandles;
	typedef typename std::map<size_t, RoomEventHandles> FloorRoomsEventHandles;
	typedef typename std::map<std::string, FloorRoomsEventHandles> EventTypeSubs;

	EventTypeSubs m_subscriberContainer;
};


#endif /* EVET_HANDLER_H__ */